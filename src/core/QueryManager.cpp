#include "QueryManager.hpp"

std::unique_ptr<pqxx::connection> wms::internal::sql::QueryManager::open_connection() const noexcept(true)
{
    std::unique_ptr<pqxx::connection> conn = nullptr;
    try
    {
		conn = std::make_unique<pqxx::connection>(this->connection_string);
    }
    catch (const std::exception& e)
    {
		std::cerr << e.what() << std::endl;
    }

    return conn;
}

void wms::internal::sql::QueryManager::close_connection(std::unique_ptr<pqxx::connection> conn) const noexcept(true)
{
	if (conn)
		conn->close();
}

pqxx::result wms::internal::sql::QueryManager::execute_query(
	const std::unique_ptr<pqxx::connection>& conn, 
	const std::string& query_string,
	const std::string& query_name) const noexcept(true)
{
	conn->prepare(query_name, query_string);
	pqxx::work work(*conn);
	pqxx::result r = work.exec_prepared(query_name);
	work.commit();

	return r;
}
