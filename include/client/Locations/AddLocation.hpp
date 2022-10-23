#ifndef ADDLOCATION_HPP
#define ADDLOCATION_HPP

#include <iostream>
#include <ctype.h>
#include <regex>
#include <vector>
#include "BaseMenu.hpp"

namespace wms
{
namespace menu
{
namespace locations
{
class AddLocation : protected wms::menu::BaseMenu
{
	public:
	AddLocation() noexcept(false);
}; // class AddLocation
}; // namespace locations
}; // namespace menu
}; // namespace wms
#endif
