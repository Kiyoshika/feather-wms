#include "BaseLocation.hpp"
#include "PickableLocation.hpp"
#include "NonPickableLocation.hpp"
#include "Util.hpp"

std::unique_ptr<wms::locations::BaseLocation> wms::locations::BaseLocation::fetch_location(
	const std::string& warehouse,
	const std::string& location_name) noexcept(false)
{
	wms::internal::sql::QueryManager query_manager;

	// used for actually returning
	std::unique_ptr<wms::locations::BaseLocation> location = nullptr;

	std::unique_ptr<pqxx::connection> conn = query_manager.open_connection();
	if (conn == nullptr)
		throw std::runtime_error("ERR: Couldn't connect to PostgreSQL server..");

	std::string sqlfile_str = wms::util::read_sql_from_file("./sql/locations/fetch_location.sql");

	wms::util::replace_substrings(sqlfile_str, {
		{ "{warehouse}", warehouse },
		{ "{name}", location_name }
	});

	pqxx::result r = query_manager.execute_query(conn, sqlfile_str, "fetch_location");
	if (r.size() == 0)
		throw std::runtime_error("ERR: Locaiton doesn't exist.");

	pqxx::row _row = r[0]; // should only be one result, so we grab it

	bool is_pickable = _row[5].as<bool>();
	bool is_active = _row[6].as<bool>();
	if (is_pickable) // pickable locations have a couple of extra variables
	{
		uint16_t aisle = _row[2].as<uint16_t>();
		uint16_t bay = _row[3].as<uint16_t>();
		uint16_t level = _row[4].as<uint16_t>();
		location = std::make_unique<wms::locations::PickableLocation>(warehouse, aisle, bay, level, is_active);
	}
	else
	{
		location = std::make_unique<wms::locations::NonPickableLocation>(warehouse, location_name, is_active);
	}

	query_manager.close_connection(std::move(conn));

	return location;
}

void wms::locations::BaseLocation::commit_update_is_active(const bool is_active) const noexcept(false)
{
	if (!this->check_location_exists())
		throw std::runtime_error("ERR: Location doesn't exist.");

	std::unique_ptr<pqxx::connection> conn = this->open_connection();
	if (conn == nullptr)
		throw std::runtime_error("ERR: Couldn't connect to PostgreSQL server.");

	std::string is_active_str = is_active ? "true" : "false";
	std::string sqlfile_str = wms::util::read_sql_from_file("./sql/locations/update_is_active.sql");
	wms::util::replace_substrings(sqlfile_str, {
		{ "{warehouse}", this->warehouse },
		{ "{name}", this->location_name },
		{ "{is_active}", is_active_str }
	});

	this->execute_query(conn, sqlfile_str, "update_is_active");
	this->close_connection(std::move(conn));
}

bool wms::locations::BaseLocation::check_location_exists() const noexcept(false)
{
	std::unique_ptr<pqxx::connection> conn = this->open_connection();
	if (conn == nullptr)
		throw std::runtime_error("ERR: Couldn't connect to PostgreSQL server.");

	std::string sqlfile_str = wms::util::read_sql_from_file("./sql/locations/check_location_exists.sql");
	wms::util::replace_substrings(sqlfile_str, {
		{ "{warehouse}", this->warehouse },
		{ "{name}", this->location_name }
	});
	
	pqxx::result res = this->execute_query(conn, sqlfile_str, "check_location_exists");
	
	bool location_exists = res.size() > 0;

	this->close_connection(std::move(conn));

	return location_exists;
}

bool wms::locations::BaseLocation::check_is_active() const noexcept(true)
{
	return this->is_active;
}
