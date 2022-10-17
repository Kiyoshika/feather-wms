#include "PickableLocation.hpp"
#include "BaseLocation.hpp"
#include "Util.hpp"
#include <pqxx/pqxx>

wms::locations::PickableLocation::PickableLocation(
		const std::string& warehouse,
		const uint16_t aisle,
		const uint16_t bay,
		const uint16_t level,
		const bool is_active) noexcept(false)
{
	if (warehouse.length() == 0)
		throw std::runtime_error("ERR: 'warehouse' must not be non-empty.");
	if (warehouse.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos)
		throw std::runtime_error("ERR: 'warehouse' must only contain letters and/or numbers.");
	if (aisle > 255)
		throw std::runtime_error("ERR: 'aisle' cannot be above 255 when creating new location.");
	if (bay > 255)
		throw std::runtime_error("ERR: 'bay' cannot be above 255 when creating new location.");
	if (level > 255)
		throw std::runtime_error("ERR: 'level' cannot be above 255 when creating new location.");

	this->warehouse = warehouse;
	this->aisle = aisle;
	this->bay = bay;
	this->level = level;
	this->location_name = this->to_string();
	this->is_active = is_active;
	this->picking_flow_int = 
		this->level + 
		(256 * this->bay) + 
		(256 * 256 * this->aisle); 
	this->is_pickable = true;
}

std::string wms::locations::PickableLocation::to_string() const noexcept(true)
{
	std::string location_string = "";
	location_string += std::to_string(this->aisle) + "-";
	location_string += std::to_string(this->bay) + "-";
	location_string += std::to_string(this->level);

	return location_string;
}

void wms::locations::PickableLocation::commit_insert() const noexcept(false)
{
	// verify location doesn't exist by searching pick flow int which is a unique
	// identifier for a location
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
		{ "{aisle}", std::to_string(this->aisle) },
		{ "{bay}", std::to_string(this->bay) },
		{ "{level}", std::to_string(this->level) },
		{ "{picking_flow_int}", std::to_string(this->picking_flow_int) },
		{ "{is_pickable}", "true" },
		{ "{is_active}", is_active_str }
	});
	
	this->execute_query(conn, sqlfile_str);
	this->close_connection(conn);
}
