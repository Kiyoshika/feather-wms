#ifndef EDITPRODUCT_HPP
#define EDITPRODUCT_HPP

#include <iostream>
#include "BaseMenu.hpp"

namespace wms
{
namespace menu
{
namespace products
{
class EditProduct : protected wms::menu::BaseMenu
{
	public:
	EditProduct() noexcept(false);
}; // class EditProduct
}; // namespace products
}; // namespace menu
}; // namespace wms

#endif
