#include "AdminMenu.hpp"

#include <iostream>

using wms::menu::AdminMenu;

int main()
{
	AdminMenu admin_menu;
	uint16_t option = admin_menu.display_and_listen();
	std::cout << "You entered option: " << option << "\n";

	return 0;
}
