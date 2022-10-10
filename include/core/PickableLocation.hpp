#ifndef PICKABLELOCATION_HPP
#define PICKABLELOCATION_HPP

#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include "QueryManager.hpp"

namespace wms
{
namespace locations 
{
class PickableLocation : protected wms::internal::sql::QueryManager
{
	public:

	// create a new location
	PickableLocation(
			const std::string& warehouse,
			const uint16_t aisle,
			const uint16_t bay,
			const uint16_t level,
			const bool is_active);

	// convert location to a string format XX-XX-XX (aisle-bay-level)
	std::string to_string() const;

	// insert location into "locations" table within database
	void commit_insert();


	std::string warehouse;
	uint16_t aisle;
	uint16_t bay;
	uint16_t level;
	uint64_t picking_flow_int;
	bool is_active;
	bool is_pickable;

	private:

	bool check_location_exists();
}; // class Location
}; // namespace entities
}; // namespace wms
#endif
