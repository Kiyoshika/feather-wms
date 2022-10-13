#include "Util.hpp"

std::string wms::util::read_sql_from_file(const std::string& filepath)
{
    std::ifstream sqlfile(filepath);
    std::stringstream buffer;
    buffer << sqlfile.rdbuf();
    return buffer.str();
}

void wms::util::replace_substring(
    std::string& main_string,
    const std::string& find_substring,
    const std::string& replace_with_substring)
{
    size_t find_index = main_string.find(find_substring);
    if (find_index == std::string::npos)
        return;
    main_string.replace(find_index, find_substring.length(), replace_with_substring);
}
