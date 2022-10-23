#include "RemoveLocation.hpp"
#include "QueryManager.hpp"
#include "Util.hpp"

wms::menu::locations::RemoveLocation::RemoveLocation() noexcept(false)
{
	this->clear_screen();

	std::string warehouse;
	std::cout << "Enter warehouse name (must be exactly 5 characters): ";
	std::cin >> warehouse;
	if (warehouse == "F1")
		return;
	if (!wms::util::is_valid_warehouse_name(warehouse))
		throw std::runtime_error("ERR: Invalid warehouse name.");

	std::string location_name;
	std::cout << "Enter location name to search: ";
	std::cin >> location_name;
	if (location_name == "F1")
		return;

	if (!wms::util::is_valid_location_name(location_name))
		throw std::runtime_error("ERR: Invalid location name.");

	wms::internal::sql::QueryManager query;
	std::unique_ptr<pqxx::connection> conn = query.open_connection();
	if (conn == nullptr)
		throw std::runtime_error("ERR: Couldn't connect to PostgreSQL server.");
	std::string sqlfile_str = wms::util::read_sql_from_file("./sql/locations/check_location_exists.sql");
	wms::util::replace_substrings(sqlfile_str, {
		{ "{warehouse}", warehouse },
		{ "{name}", location_name }
	});
	pqxx::result res = query.execute_query(conn, sqlfile_str, "check_location_exists");
	if (res.size() == 0)
		throw std::runtime_error("ERR: Location doesn't exist.");
	sqlfile_str = wms::util::read_sql_from_file("./sql/locations/delete_location.sql");
	wms::util::replace_substrings(sqlfile_str, {
		{ "{warehouse}" , warehouse },
		{ "{name}", location_name }
	});
	query.execute_query(conn, sqlfile_str, "delete_location");
	
	query.close_connection(std::move(conn));
}
