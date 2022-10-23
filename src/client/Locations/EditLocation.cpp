#include "EditLocation.hpp"
#include "PickableLocation.hpp"
#include "NonPickableLocation.hpp"
#include "Util.hpp"

wms::menu::locations::EditLocation::EditLocation() noexcept(false)
{
	this->clear_screen();

	std::string warehouse;
	std::cout << "Enter warehouse name (must be exactly 5 characters): ";
	std::cin >> warehouse;
	if (warehouse == "F1")
		return;
	if (!wms::util::is_valid_warehouse_name(warehouse))
		throw std::runtime_error("ERR: Invalid warehouse name.");

	std::string location_name;
	std::cout << "Enter location name to search: ";
	std::cin >> location_name;
	if (location_name == "F1")
		return;

	if (!wms::util::is_valid_location_name(location_name))
		throw std::runtime_error("ERR: Invalid location name.");

	// this can throw an exception which will propogate to the LocationMenu
	wms::locations::BaseLocation* location = wms::locations::BaseLocation::fetch_location(
		warehouse,
		location_name);

	std::string is_active_str = location->check_is_active() ? "y" : "n";
	std::string set_active = "";
	while (set_active != "y" && set_active != "Y" && set_active != "n" && set_active != "N")
	{
		std::cout << "\nSet location active (y/n)? (Currently: " + is_active_str + "): ";
		std::cin >> set_active;
		if (set_active == "F1")
			return;
	}

	bool set_active_b = false;
	if (set_active == "y" || set_active == "Y")
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
