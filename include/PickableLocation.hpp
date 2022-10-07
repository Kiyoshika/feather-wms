#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <stdexcept>
#include <string>

namespace wms
{
namespace locations 
{
class PickableLocation
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

		// get aisle number from location
		uint16_t get_aisle() const;

		// get bay number from location
		uint16_t get_bay() const;

		// get level number from location
		uint16_t get_level() const;

		// set whether or not the location is currently active
		void set_active(const bool is_active);

	private:
		std::string warehouse;
		uint16_t aisle;
		uint16_t bay;
		uint16_t level;
		uint64_t picking_flow_int;

		bool is_active;
}; // class Location
}; // namespace entities
}; // namespace wms
#endif
