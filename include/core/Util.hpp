#ifndef UTIL_HPP
#define UTIL_HPP

#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

namespace wms
{
namespace util
{
    std::string read_sql_from_file(const std::string& filepath);

    void replace_substring(
        std::string& main_string,
        const std::string& find_substring,
        const std::string& replace_with_substring);

}; // namespace util
}; // namespace wms
#endif
