#include "PickableLocation.hpp"
#include <pqxx/pqxx>

wms::locations::PickableLocation::PickableLocation(
		const std::string& warehouse,
		const uint16_t aisle,
		const uint16_t bay,
		const uint16_t level,
		const bool is_active)
{
	if (warehouse.length() == 0)
		throw std::runtime_error("ERR: 'warehouse' must not be non-empty.");
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
	this->is_active = is_active;
	this->picking_flow_int = 
		this->level + 
		(256 * this->bay) + 
		(256 * 256 * this->aisle); 
}

std::string wms::locations::PickableLocation::get_warehouse() const
{
	return this->warehouse;
}

std::string wms::locations::PickableLocation::to_string() const
{
	std::string location_string = "";
	location_string += std::to_string(this->aisle) + "-";
	location_string += std::to_string(this->bay) + "-";
	location_string += std::to_string(this->level);

	return location_string;
}

uint16_t wms::locations::PickableLocation::get_aisle() const
{
	return this->aisle;
}

uint16_t wms::locations::PickableLocation::get_bay() const
{
	return this->bay;
}

uint16_t wms::locations::PickableLocation::get_level() const
{
	return this->level;
}

uint64_t wms::locations::PickableLocation::get_picking_flow_int() const
{
	return this->picking_flow_int;
}

void wms::locations::PickableLocation::set_active(const bool is_active)
{
	this->is_active = is_active;
}

void wms::locations::PickableLocation::commit_insert() const
{
	// verify location doesn't exist by searching pick flow int which is a unique
	// identifier for a location

	try
	{
		// TODO: create query manager to avoid hardcoding these types of things
		pqxx::connection conn("postgresql://fwmsadmin@localhost:5432/fwmsprod");
		pqxx::work work(conn);
		pqxx::result r = work.exec("SELECT 1 FROM locations WHERE warehouse = '" + this->warehouse + "' AND picking_flow_int = " + std::to_string(this->picking_flow_int) + ";");
		work.commit();
		
		if (r.size() > 0)
			throw std::runtime_error("ERR: Location already exists.");
		else
			std::cout << "TODO: insert location into database!\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return;
	}
}