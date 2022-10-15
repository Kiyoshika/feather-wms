#include "BaseMenu.hpp"
#include "AdminMenu.hpp"
#include "AddLocation.hpp"

wms::menu::AdminMenu::AdminMenu()
{
	this->set_title("Admin Menu");
	this->add_options({
		{ 1, "Add Location", [](){
			wms::menu::locations::AddLocation add;
		}},

		{ 2, "Edit Location", [](){
			std::cout << "Edit a location!\n";
		}},

		{ 3, "Remove Location", [](){
			std::cout << "Remove a location!\n";
		}}
	});
}
