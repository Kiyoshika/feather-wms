#include "BaseMenu.hpp"
#include "ProductMenu.hpp"
#include "AddProduct.hpp"
#include "EditProduct.hpp"
#include "RemoveProduct.hpp"

wms::menu::ProductMenu::ProductMenu()
{
	this->set_title("Product Menu");
	this->add_options({
		{ 1, "Add Product", [](){
			wms::menu::products::AddProduct add;
		}},

		{ 2, "Edit Product", [](){
			// wms::menu::products::EditProduct edit;
		}},

		{ 3, "Remove Product", [](){
			// wms::menu::products::RemoveProduct remove;
		}}
	});
}
