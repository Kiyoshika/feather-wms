#include "Util.hpp"
#include <pqxx/pqxx>

std::string wms::util::read_sql_from_file(const std::string& filepath) noexcept(false)
{
	if (!std::filesystem::exists(filepath))
		throw std::runtime_error("ERR: SQL file '" + filepath + "' doesn't exist.");

    std::ifstream sqlfile(filepath);
    std::stringstream buffer;
    buffer << sqlfile.rdbuf();
    return buffer.str();
}

inline void wms::util::replace_substring(
    std::string& main_string,
    const std::string& find_substring,
    const std::string& replace_with_substring) noexcept(true)
{
    size_t find_index; 
	while ((find_index = main_string.find(find_substring)) != std::string::npos)
		main_string.replace(find_index, find_substring.length(), replace_with_substring);
}

void wms::util::replace_substrings(
	std::string& main_string,
	const std::vector<std::pair<std::string, std::string>>& replace_list) noexcept(true)
{
	for (const auto& [find_str, replace_str] : replace_list)
		wms::util::replace_substring(main_string, find_str, replace_str);
}


bool wms::util::is_valid_warehouse_name(const std::string& warehouse) noexcept(true)
{
	if (warehouse.length() != 5)
		return false;

	if (warehouse.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos)
		return false;

	return true;

}

bool wms::util::is_valid_location_name(const std::string& location_name) noexcept(true)
{
	if (location_name.length() < 5)
		return false;

	if (location_name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_") != std::string::npos)
		return false;

	return true;

}
