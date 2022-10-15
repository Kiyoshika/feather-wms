#ifndef QUERYMANAGER_HPP
#define QUERYMANAGER_HPP

#include <pqxx/pqxx>
#include <stdexcept>
#include <iostream>

namespace wms
{
namespace internal
{
namespace sql
{
class QueryManager
{
    protected:
        pqxx::connection* open_connection() const noexcept(true);
        void close_connection(pqxx::connection*& conn) const noexcept(true);

        const std::string connection_string = "host=localhost dbname=fwmsprod user=fwmsuser password=sample";
}; // class QueryManager
}; // namespace sql
}; // namespace internal
}; //namespace wms
#endif
