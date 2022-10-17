#include "QueryManager.hpp"

pqxx::connection* wms::internal::sql::QueryManager::open_connection() const noexcept(true)
{
    pqxx::connection* conn = nullptr;
    try
    {
        conn = new pqxx::connection(this->connection_string);
    }
    catch (const std::exception& e)
    {
        //delete conn; // should be no-op, but doing it anyways
		std::cerr << e.what() << std::endl;
    }

    return conn;
}

void wms::internal::sql::QueryManager::close_connection(pqxx::connection*& conn) const noexcept(true)
{
	if (conn)
	{
		conn->close();
		delete conn;
		conn = nullptr;
	}
}

pqxx::result wms::internal::sql::QueryManager::execute_query(
	pqxx::connection*& conn, 
	const std::string& query_string) const noexcept(true)
{
	conn->prepare("query", query_string);
	pqxx::work work(*conn);
	pqxx::result r = work.exec_prepared("query");
	work.commit();

	return r;
}
