#ifndef PICKABLELOCATION_HPP
#define PICKABLELOCATION_HPP

#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include "BaseLocation.hpp"

namespace wms
{
namespace locations 
{
class PickableLocation : public wms::locations::BaseLocation
{
	public:
	// create a new location
	PickableLocation(
			const std::string& warehouse,
			const uint16_t aisle,
			const uint16_t bay,
			const uint16_t level,
			const bool is_active) noexcept(false);

	// convert location to a string format XX-XX-XX (aisle-bay-level)
	std::string to_string() const noexcept(true);

	// insert location into "locations" table within database
	void commit_insert() const noexcept(false) override;

	private:
	uint16_t aisle;
	uint16_t bay;
	uint16_t level;
	uint64_t picking_flow_int;

}; // class PickableLocation
}; // namespace locations 
}; // namespace wms
#endif
