#ifndef NONPICKABLELOCATION_HPP
#define NONPICKABLELOCATION_HPP

#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include "BaseLocation.hpp"

namespace wms
{
namespace locations
{
class NonPickableLocation : public wms::locations::BaseLocation
{
	public:
	NonPickableLocation(
		const std::string& warehouse,
		const std::string& location_name,
		const bool is_active) noexcept(false);

	void commit_insert() const noexcept(false) override;

}; // class NonPickableLocation
}; // namespace locations
}; // namespace wms
#endif
