#include "AdminMenu.hpp"
#include "LocationMenu.hpp"

wms::menu::AdminMenu::AdminMenu()
{
	this->set_title("Admin Menu");
	this->add_options({
		{ 1, "Location Config", [](){
			wms::menu::LocationMenu location;
			location.display_and_listen();
		}}
	});
}
