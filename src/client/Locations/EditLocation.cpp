#include "EditLocation.hpp"
#include "PickableLocation.hpp"
#include "NonPickableLocation.hpp"

wms::menu::locations::EditLocation::EditLocation() noexcept(false)
{
	this->clear_screen();

	std::string location_name;
	std::cout << "Enter location name to search: ";
	std::cin >> location_name;

	wms::locations::BaseLocation* location = wms::locations::BaseLocation::fetch_location(
		"TEST1",
		location_name);

	std::string is_active_str = location->check_is_active() ? "y" : "n";
	char set_active = 0;
	while (set_active != 'y' && set_active != 'Y' && set_active != 'n' && set_active != 'N')
	{
		std::cout << "\nSet location active (y/n)? (Currently: " + is_active_str + "): ";
		std::cin >> set_active;
	}

	bool set_active_b = false;
	if (set_active == 'y' || set_active == 'Y')
		set_active_b = true;

	try
	{
		location->commit_update_is_active(set_active_b);
		delete location;
		location = nullptr;
	}
	catch (const std::exception& e)
	{
		delete location;
		location = nullptr;	
		std::cerr << e.what() << std::endl;
	}
}
