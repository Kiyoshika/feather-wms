#include "BaseMenu.hpp"
#include "AdminMenu.hpp"

wms::menu::AdminMenu::AdminMenu()
{
	this->set_title("Admin Menu");
	this->add_options({
		{ 1, "Add Location" },
		{ 2, "Edit Location" },
		{ 3, "Remove Location" }
	});
}
