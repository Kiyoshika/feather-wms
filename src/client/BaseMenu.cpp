#include "BaseMenu.hpp"

wms::menu::BaseMenu::BaseMenu()
{
	/* nothing */
}

wms::menu::BaseMenu::BaseMenu(const std::string& title)
	: title{title}
{
	/* nothing */
}

wms::menu::BaseMenu::BaseMenu(
	const std::string& title,
	const std::vector<std::pair<uint16_t, std::string>>& options)
	: title{title}, options{options}
{
	/* nothing */
}

void wms::menu::BaseMenu::clear_screen() const
{
	for (size_t i = 0; i < 1000; ++i)
		std::cout << "\n";
}

void wms::menu::BaseMenu::display_title() const
{
	std::cout << "==== " + this->title + " ====\n\n";
}

void wms::menu::BaseMenu::set_title(const std::string& title)
{
	this->title = title;
}

void wms::menu::BaseMenu::add_option(const std::pair<uint16_t, std::string>& option)
{
	this->options.push_back(option);
}

void wms::menu::BaseMenu::add_options(const std::vector<std::pair<uint16_t, std::string>>& options)
{
	for (const std::pair<uint16_t, std::string>& option : options)
		this->options.push_back(option);
}

uint16_t wms::menu::BaseMenu::listen_for_input() const
{
	if (this->options.size() == 0)
		throw std::runtime_error("listen_for_input: 'allowed_options' must have at least one element.");

	// keep listening for input until user provides a valid option
	while (true)
	{
		uint16_t user_input;
		std::cin >> user_input;
		for (const auto& [idx, option] : this->options)
			if (user_input == idx)
				return idx;
		this->display("ERR: Invalid Input"); // refresh screen
	}
	
	return 0; // technically unreachable but need to satisfy compiler
}

void wms::menu::BaseMenu::display(std::string msg) const
{
	this->clear_screen();
	this->display_title();

	for (const auto& [idx, option] : this->options)
		std::cout << std::to_string(idx) + ") " + option << std::endl;

	if (msg.length() > 0)
		std::cout << "\n" << msg << "\n";;

	std::cout << "\n>> "; 
}

uint16_t wms::menu::BaseMenu::display_and_listen(std::string msg) const
{
	this->display(msg);
	return this->listen_for_input();
}
