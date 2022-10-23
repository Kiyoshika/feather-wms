#ifndef REMOVEPRODUCT_HPP
#define REMOVEPRODUCT_HPP

#include <iostream>
#include "BaseMenu.hpp"

namespace wms
{
namespace menu
{
namespace products
{
class RemoveProduct : protected wms::menu::BaseMenu
{
	public:
	RemoveProduct() noexcept(false);
}; // class RemoveProduct
}; // namespace products
}; // namespace menu
}; // namespace wms


#endif
