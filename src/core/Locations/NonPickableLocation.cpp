#include "NonPickableLocation.hpp"
#include "BaseLocation.hpp"
#include "Util.hpp"
#include <pqxx/pqxx>

wms::locations::NonPickableLocation::NonPickableLocation(
	const std::string& warehouse,
	const std::string& location_name,
	const bool is_active) noexcept(false)
{
	if (!wms::util::is_valid_warehouse_name(warehouse))
		throw std::runtime_error("ERR: Invalid warehouse name.");
	
	if (!wms::util::is_valid_location_name(location_name))
		throw std::runtime_error("ERR: Invalid location mame.");

	this->warehouse = warehouse;
	this->location_name = location_name;
	this->is_active = is_active;
	this->is_pickable = false;
}

void wms::locations::NonPickableLocation::commit_insert() const noexcept(false)
{
	// verify location doesn't exist by searching location name
	if (this->check_location_exists())
		throw std::runtime_error("ERR: Location already exists.");

	std::unique_ptr<pqxx::connection> conn = this->open_connection();
	if (conn == nullptr)
		throw std::runtime_error("ERR: Couldn't connect to PostgreSQL server.");

	std::string sqlfile_str = wms::util::read_sql_from_file("./sql/locations/insert_new_location.sql");
	std::string is_active_str = this->is_active ? "true" : "false";

	wms::util::replace_substrings(sqlfile_str, {
		{ "{warehouse}", this->warehouse },
		{ "{name}", this->location_name },
		{ "{aisle}", "NULL" },
		{ "{bay}", "NULL" },
		{ "{level}", "NULL" },
		{ "{picking_flow_int}", "NULL" },
		{ "{is_pickable}", "false" },
		{ "{is_active}", is_active_str }
	});

	this->execute_query(conn, sqlfile_str, "insert_new_location_nonpickable");
	this->close_connection(std::move(conn));
}
