#include "AdminMenu.hpp"
#include "LocationMenu.hpp"
#include "ProductMenu.hpp"

wms::menu::AdminMenu::AdminMenu()
{
	this->set_title("Admin Menu");
	this->add_options({
		{ 1, "Location Config", [](){
			wms::menu::LocationMenu location;
			location.display_and_listen();
		}},

		{ 2, "Product Config", [](){
			wms::menu::ProductMenu product;
			product.display_and_listen();
		}}
	});
}
