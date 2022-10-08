#ifndef PICKABLELOCATION_HPP
#define PICKABLELOCATION_HPP

#include <stdexcept>
#include <string>
#include <iostream>

namespace wms
{
namespace locations 
{
struct PickableLocation
{
	// create a new location
	PickableLocation(
			const std::string& warehouse,
			const uint16_t aisle,
			const uint16_t bay,
			const uint16_t level,
			const bool is_active);

	// get warehouse from location
	std::string get_warehouse() const;

	// convert location to a string format XX-XX-XX (aisle-bay-level)
	std::string to_string() const;

	// get aisle number from location
	uint16_t get_aisle() const;

	// get bay number from location
	uint16_t get_bay() const;

	// get level number from location
	uint16_t get_level() const;

	// get picking flow integer (unique identifier) for location
	uint64_t get_picking_flow_int() const;

	// set whether or not the location is currently active
	void set_active(const bool is_active);

	// insert location into "locations" table within database
	void commit_insert() const;


	std::string warehouse;
	uint16_t aisle;
	uint16_t bay;
	uint16_t level;
	uint64_t picking_flow_int;

	bool is_active;
	bool is_pickable;
}; // class Location
}; // namespace entities
}; // namespace wms
#endif
