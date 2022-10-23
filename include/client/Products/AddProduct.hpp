#ifndef ADDPRODUCT_HPP
#define ADDPRODUCT_HPP

#include <iostream>
#include "BaseMenu.hpp"

namespace wms
{
namespace menu
{
namespace products
{
class AddProduct : protected wms::menu::BaseMenu
{
	public:
	AddProduct() noexcept(false);
}; // class AddProduct
}; // namespace products
}; // namespace menu
}; // namespace wms

#endif 
