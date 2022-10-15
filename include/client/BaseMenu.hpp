#ifndef BASEMENU_HPP
#define BASEMENU_HPP

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>
#include <tuple>
#include <functional>

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
		const std::vector<std::tuple<uint16_t, std::string, std::function<void()>>>& options);
	void display(std::string msg = "") const;
	void display_and_listen(std::string msg = "") const;
	void set_title(const std::string& title);
	void add_option(const std::tuple<uint16_t, std::string, std::function<void()>>& option);
	void add_options(const std::vector<std::tuple<uint16_t, std::string, std::function<void()>>>& options);

	protected:
	void clear_screen() const;
	void display_title() const;
	void listen_for_input() const;
	std::string title;
	std::vector<std::tuple<uint16_t, std::string, std::function<void()>>> options;
}; // class BaseMenu
}; // namespace menu
}; // namespace wms
#endif
