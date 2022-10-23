#include "AdminMenu.hpp"

#include <iostream>

using wms::menu::AdminMenu;

int main()
{
	AdminMenu admin_menu;
	std::string err_msg = "";

	while (true)
	{
		try
		{
			admin_menu.display_and_listen(err_msg);
			err_msg = "";
		}
		catch (const std::exception& e)
		{
			err_msg = e.what();
		}
	}

	return 0;
}
