#ifndef BASEMENU_HPP
#define BASEMENU_HPP

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>

namespace wms
{
namespace menu
{
class BaseMenu
{
	public:
	BaseMenu();
	BaseMenu(const std::string& title);
	BaseMenu(
		const std::string& title,
		const std::vector<std::pair<uint16_t, std::string>>& options);
	void display(std::string msg = "") const;
	uint16_t display_and_listen(std::string msg = "") const;
	void set_title(const std::string& title);
	void add_option(const std::pair<uint16_t, std::string>& option);
	void add_options(const std::vector<std::pair<uint16_t, std::string>>& options);

	private:
	void clear_screen() const;
	void display_title() const;
	uint16_t listen_for_input() const;

	std::string title;
	std::vector<std::pair<uint16_t, std::string>> options;
}; // class BaseMenu
}; // namespace menu
}; // namespace wms
#endif
