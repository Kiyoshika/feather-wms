#ifndef BASELOCATION_HPP
#define BASELOCATION_HPP

#include "QueryManager.hpp"
#include <string>
#include <pqxx/pqxx>
#include <memory>

namespace wms
{
namespace locations
{
class BaseLocation : public wms::internal::sql::QueryManager
{
	public:
	static std::unique_ptr<BaseLocation> fetch_location(
		const std::string& warehouse,
		const std::string& location_name);
	virtual void commit_insert() const noexcept(false) = 0;
	void commit_update_is_active(const bool is_active) const noexcept(false);
	bool check_is_active() const noexcept(true);
	virtual ~BaseLocation() = default;
	
	protected:
	bool check_location_exists() const noexcept(false);

	std::string warehouse;
	std::string location_name;
	bool is_active;
	bool is_pickable;
}; // class BaseLocation
}; // namespace locations
}; // namespace wms

#endif
