#include "AddLocation.hpp"
#include "PickableLocation.hpp"
#include "NonPickableLocation.hpp"
#include "Util.hpp"

bool _is_valid_location_name(
	const std::string& location_name,
	char is_pickable,
	std::string& err_msg,
	std::vector<uint16_t>& location_tokens)
{
	location_tokens.clear();

	if (is_pickable == 'y' || is_pickable == 'Y')
	{
		std::vector<std::string> location_name_tokens = {};

		std::string buffer;
		std::stringstream location_stream(location_name);

		if(std::regex_match(location_name, std::regex("[0-9]*-[0-9]*-[0-9]*")))
		{
			while (std::getline(location_stream, buffer, '-'))
				location_name_tokens.push_back(buffer);
			
			for (const std::string& location_token_str : location_name_tokens)
			{
				uint16_t location_token = std::stol(location_token_str);
				if (location_token > 255 || location_token < 1)
					goto badformat;
				location_tokens.push_back(location_token);
			}

			return true;
		}

		badformat:
		err_msg = "\nERR: Location format must be X-X-X where X is between 1 and 255.";
		return false;
	}
	else if (location_name.length() >= 5)
		return true;

	err_msg = "\nERR: Location must be at least 5 characters long!";
	return false;
}

wms::menu::locations::AddLocation::AddLocation() noexcept(false)
{
	this->clear_screen();
	
	std::string warehouse;
	std::cout << "Enter warehouse name (must be exactly 5 characters): ";
	std::cin >> warehouse;
	if (!wms::util::is_valid_warehouse_name(warehouse))
		throw std::runtime_error("ERR: Invalid warehouse name.");

	char is_pickable = 0;
	while (is_pickable != 'y' && is_pickable != 'Y' && is_pickable != 'n' && is_pickable != 'N')
	{
		std::cout << "\nIs location pickable? (y/n): ";
		std::cin >> is_pickable;
	}

	char is_active = 0;
	while (is_active != 'y' && is_active != 'Y' && is_active != 'n' && is_active != 'N')
	{
		std::cout << "\nIs location currently active? (y/n): ";
		std::cin >> is_active;
	}

	std::string location_msg = "";
	if (is_pickable == 'y' || is_pickable == 'Y')
		location_msg = "\nLocation Name (Format: X-X-X, X ranges from 1-255): ";
	else
		location_msg = "\nLocation Name (Must be at least 5 characters): ";

	std::string location_name = "";
	std::string err_msg = "";
	std::vector<uint16_t> location_tokens = {};	
	while (true)
	{
		std::cout << location_msg;
		std::cin >> location_name;
		if (_is_valid_location_name(location_name, is_pickable, err_msg, location_tokens))
			break;
		std::cout << err_msg;
	}

	bool is_active_b;
	if (is_active == 'y' || is_active == 'Y')
		is_active_b = true;
	else
		is_active_b = false;

	// add location to database
	if (is_pickable == 'y' || is_pickable == 'Y')
	{
		wms::locations::PickableLocation loc(
			warehouse,
			location_tokens[0],
			location_tokens[1],
			location_tokens[2],
			is_active_b);

		loc.commit_insert();
	}
	else // non-pickable
	{
		wms::locations::NonPickableLocation loc(
			warehouse,
			location_name,
			is_active_b);

		loc.commit_insert();
	}
}
