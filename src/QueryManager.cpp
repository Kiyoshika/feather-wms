#include "QueryManager.hpp"

pqxx::connection* wms::internal::sql::QueryManager::open_connection()
{
    pqxx::connection* conn = nullptr;
    try
    {
        conn = new pqxx::connection(this->connection_string);
    }
    catch (const std::exception& e)
    {
        delete conn; // should be no-op, but doing it anyways
		std::cerr << e.what() << std::endl;
    }

    return conn;
}

void wms::internal::sql::QueryManager::close_connection(pqxx::connection*& conn)
{
    conn->close();
    delete conn;
    conn = nullptr;
}