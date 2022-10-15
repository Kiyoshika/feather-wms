#include "PickableLocation.hpp"
#include "Util.hpp"

bool wms::locations::PickableLocation::check_location_exists() noexcept(true)
{
    bool location_exists = false;

	pqxx::connection* conn = this->open_connection();
	if (conn == nullptr)
		return false;

	std::string sqlfile_str = wms::util::read_sql_from_file("./sql/locations/check_pickable_location_exists.sql");
	wms::util::replace_substring(sqlfile_str, "{warehouse}", "'" + this->warehouse + "'");
	wms::util::replace_substring(sqlfile_str, "{picking_flow_int}", std::to_string(this->picking_flow_int));

	pqxx::work work(*conn);
	pqxx::result r = work.exec(sqlfile_str);
	work.commit();
	
	location_exists = r.size() > 0;
	
	this->close_connection(conn);

    return location_exists;
}
