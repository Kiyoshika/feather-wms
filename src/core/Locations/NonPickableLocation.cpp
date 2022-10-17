#include "NonPickableLocation.hpp"
#include "BaseLocation.hpp"
#include "Util.hpp"
#include <pqxx/pqxx>

wms::locations::NonPickableLocation::NonPickableLocation(
	const std::string& warehouse,
	const std::string& location_name,
	const bool is_active) noexcept(false)
{
	if (warehouse.length() == 0)
		throw std::runtime_error("ERR: 'warehouse' must be non-empty.");
	if (warehouse.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos)
		throw std::runtime_error("ERR: 'warehouse' must only contain letters and/or numbers.");
	if (location_name.length() < 5)
		throw std::runtime_error("ERR: 'location_name' must be at least 5 characters long");
	if (location_name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_") != std::string::npos)
		throw std::runtime_error("ERR: 'location_name' must only contain letters, numbers, hyphens (-) or underscores (_)..");

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

	pqxx::connection* conn = this->open_connection();
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

	this->execute_query(conn, sqlfile_str);
	this->close_connection(conn);
}
