#ifndef NONPICKABLELOCATION_HPP
#define NONPICKABLELOCATION_HPP

#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include "QueryManager.hpp"

namespace wms
{
namespace locations
{
class NonPickableLocation : protected wms::internal::sql::QueryManager
{
	public:

	NonPickableLocation(
		const std::string& warehouse,
		const std::string& location_name,
		const bool is_active) noexcept(false);

	void commit_insert() noexcept(false);

	std::string warehouse;
	std::string location_name;
	bool is_active;
	bool is_pickable;

	private:

	bool check_location_exists() noexcept(true);
}; // class NonPickableLocation
}; // namespace locations
}; // namespace wms
#endif
