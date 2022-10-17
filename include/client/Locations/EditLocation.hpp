#ifndef EDITLOCATION_HPP
#define EDITLOCATION_HPP

#include <string>
#include <stdexcept>
#include "BaseMenu.hpp"

namespace wms
{
namespace menu
{
namespace locations
{
class EditLocation : protected wms::menu::BaseMenu
{
	public:
	EditLocation() noexcept(false);
}; // class EditLocation
}; // namespace locations
}; // namespace menu
}; // namespace wms
#endif
