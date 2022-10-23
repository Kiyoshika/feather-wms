#include "BaseMenu.hpp"
#include <stdexcept>

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
	const std::vector<std::tuple<uint16_t, std::string, std::function<void()>>>& options)
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

void wms::menu::BaseMenu::add_option(const std::tuple<uint16_t, std::string, std::function<void()>>& option)
{
	this->options.push_back(option);
}

void wms::menu::BaseMenu::add_options(const std::vector<std::tuple<uint16_t, std::string, std::function<void()>>>& options)
{
	for (const std::tuple<uint16_t, std::string, std::function<void()>>& option : options)
		this->options.push_back(option);
}

void wms::menu::BaseMenu::listen_for_input() const
{
	if (this->options.size() == 0)
		throw std::runtime_error("listen_for_input: 'allowed_options' must have at least one element.");

	// keep listening for input until user provides a valid option
	while (true)
	{
		std::string user_input;
		std::cin >> user_input;

		if (user_input == "F1")
			return;

		try
		{
			for (const auto& [idx, option, callback] : this->options)
				if (std::stol(user_input) == idx)
					return callback();
		}
		catch (const std::exception& e)
		{
			this->display(e.what()); // refresh screen
		}
	}
}

void wms::menu::BaseMenu::display(std::string msg) const
{
	this->clear_screen();
	this->display_title();

	for (const auto& [idx, option, callback] : this->options)
		std::cout << std::to_string(idx) + ") " + option << std::endl;

	if (msg.length() > 0)
		std::cout << "\n" << msg << "\n";;

	std::cout << "\n>> "; 
}

void wms::menu::BaseMenu::display_and_listen(std::string msg) const
{
	this->display(msg);
	this->listen_for_input();
}
