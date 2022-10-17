#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <stdexcept>
#include <utility>
#include <vector>

namespace wms
{
namespace util
{
    std::string read_sql_from_file(const std::string& filepath) noexcept(false);

    inline void replace_substring(
        std::string& main_string,
        const std::string& find_substring,
        const std::string& replace_with_substring) noexcept(true);

	void replace_substrings(
		std::string& main_string,
		const std::vector<std::pair<std::string, std::string>>& replace_list) noexcept(true);

	bool is_valid_warehouse_name(const std::string& warehouse) noexcept(true);

	bool is_valid_location_name(const std::string& location_name) noexcept(true);

}; // namespace util
}; // namespace wms
#endif
