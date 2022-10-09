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
        pqxx::connection* open_connection();
        void close_connection(pqxx::connection*& conn);

        const std::string connection_string = "postgresql://fwmsadmin@localhost:5432/fwmsprod";
}; // class QueryManager
}; // namespace sql
}; // namespace internal
}; //namespace wms
#endif