#include "LocationMenu.hpp"

wms::menu::LocationMenu::LocationMenu()
{
	this->set_title("Location Menu");
	this->add_options({
		{ 1, "Add Location", [](){
			wms::menu::locations::AddLocation add;
		}},

		{ 2, "Edit Location", [](){
			wms::menu::locations::EditLocation edit;
		}},

		{ 3, "Remove Location", [](){
			wms::menu::locations::RemoveLocation remove;
		}}
	});
}
