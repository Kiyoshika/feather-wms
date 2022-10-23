#ifndef QUERYMANAGER_HPP
#define QUERYMANAGER_HPP

#include <pqxx/pqxx>
#include <stdexcept>
#include <iostream>
#include <string>
#include <memory>

namespace wms
{
namespace internal
{
namespace sql
{
class QueryManager
{
    public:
        std::unique_ptr<pqxx::connection> open_connection() const noexcept(true);
        void close_connection(std::unique_ptr<pqxx::connection> conn) const noexcept(true);
		pqxx::result execute_query(
			const std::unique_ptr<pqxx::connection>& conn,
			const std::string& query_string,
			const std::string& query_name) const noexcept(true);
	private:
        const std::string connection_string = "host=localhost dbname=fwmsprod user=fwmsuser password=sample";
}; // class QueryManager
}; // namespace sql
}; // namespace internal
}; //namespace wms
#endif
