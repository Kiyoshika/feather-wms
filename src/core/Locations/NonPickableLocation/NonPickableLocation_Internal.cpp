#include "NonPickableLocation.hpp"
#include "Util.hpp"

bool wms::locations::NonPickableLocation::check_location_exists() noexcept(true)
{
	bool location_exists = false;

	pqxx::connection* conn = this->open_connection();
	if (conn == nullptr)
		return false;

	std::string sqlfile_str = wms::util::read_sql_from_file("./sql/locations/check_nonpickable_location_exists.sql");
	wms::util::replace_substring(sqlfile_str, "{warehouse}", "'" + this->warehouse + "'");
	wms::util::replace_substring(sqlfile_str, "{location_name}", "'" + this->location_name + "'");

	pqxx::work work(*conn);
	pqxx::result r = work.exec(sqlfile_str);
	work.commit();

	location_exists = r.size() > 0;

	this->close_connection(conn);

	return location_exists;
}
