#include "BaseMenu.hpp"
#include "AdminMenu.hpp"
#include "AddLocation.hpp"
#include "EditLocation.hpp"
#include "RemoveLocation.hpp"

wms::menu::AdminMenu::AdminMenu()
{
	this->set_title("Admin Menu");
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
