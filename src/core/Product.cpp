#include "Product.hpp"
#include "QueryManager.hpp"
#include "Util.hpp"

wms::products::Product::Product(
	const std::string& sku,
	const std::string& upc,
	const std::string& name,
	const std::string& description,
	const double item_cost,
	const double listing_price,
	const double length,
	const double width,
	const double height,
	const double weight,
	const bool is_active) noexcept(true) :
	sku{sku}, upc{upc}, name{name}, description{description},
	item_cost{item_cost}, listing_price{listing_price},
	length{length}, width{width}, height{height}, weight{weight},
	is_active{is_active}
{
}

bool wms::products::Product::check_product_exists() const noexcept(false)
{
	wms::internal::sql::QueryManager query;
	std::unique_ptr<pqxx::connection> conn = query.open_connection();
	if (conn == nullptr)
		throw std::runtime_error("ERR: Couldn't connect to PostgreSQL server.");

	std::string sqlfile_str = wms::util::read_sql_from_file("./sql/products/check_product_exists.sql");
	wms::util::replace_substrings(sqlfile_str, {
		{ "{sku}", this->sku } // sku is a unique identifier
	});

	pqxx::result res = query.execute_query(conn, sqlfile_str, "check_product_exists");

	bool product_exists = res.size() > 0;

	query.close_connection(std::move(conn));

	return product_exists;
}

void wms::products::Product::commit_insert() const noexcept(false)
{
	if (this->check_product_exists())
		throw std::runtime_error("ERR: Product already exists");

	wms::internal::sql::QueryManager query;	
	std::unique_ptr<pqxx::connection> conn = query.open_connection();
	if (conn == nullptr)
		throw std::runtime_error("ERR: Couldn't connect to PostgreSQL server.");

	std::string sqlfile_str = wms::util::read_sql_from_file("./sql/products/insert_new_product.sql");
	std::string _description = this->description.length() > 0 ? ("'" + this->description + "'") : "NULL";
	std::string _is_active = this->is_active ? "true" : "false";
	wms::util::replace_substrings(sqlfile_str, {
		{ "{sku}", this->sku },
		{ "{upc}", this->upc },
		{ "{name}", this->name },
		{ "{description}", _description },
		{ "{item_cost}", std::to_string(this->item_cost) },
		{ "{listing_price}", std::to_string(this->listing_price) },
		{ "{length}", std::to_string(this->length) },
		{ "{width}", std::to_string(this->width) },
		{ "{height}", std::to_string(this->height) },
		{ "{weight}", std::to_string(this->weight) },
		{ "{is_active}", _is_active }
	});
	query.execute_query(conn, sqlfile_str, "insert_new_product");
	query.close_connection(std::move(conn));
}

std::unique_ptr<wms::products::Product> wms::products::Product::fetch_product(const std::string& sku) noexcept(false)
{
	if (!wms::util::is_valid_sku(sku))
		throw std::runtime_error("ERR: Invalid SKU format.");

	wms::internal::sql::QueryManager query;
	std::unique_ptr<pqxx::connection> conn = query.open_connection();

	std::string sqlfile_str = wms::util::read_sql_from_file("./sql/products/fetch_product.sql");

	wms::util::replace_substrings(sqlfile_str, {
		{ "{sku}", sku }
	});

	pqxx::result r = query.execute_query(conn, sqlfile_str, "fetch_product");

	if (r.size() == 0)
		throw std::runtime_error("ERR: Product doesn't exist.");
	
	pqxx::row _row = r[0]; // should only be one result, so we grab it

	std::unique_ptr<wms::products::Product> product = std::make_unique<wms::products::Product>(
		_row[0].as<std::string>(), 	// sku
		_row[1].as<std::string>(), 	// upc
		_row[2].as<std::string>(), 	// name
		_row[3].as<std::string>(), 	// description
		_row[4].as<double>(), 		// item cost
		_row[5].as<double>(),		// listing price
		_row[6].as<double>(),		// length
		_row[7].as<double>(),		// width
		_row[8].as<double>(),		// height
		_row[9].as<double>(),		// weight
		_row[10].as<bool>()			// is active
	);
	
	query.close_connection(std::move(conn));

	return product;
}

void wms::products::Product::commit_remove() const noexcept(false)
{
	if (!this->check_product_exists())
		throw std::runtime_error("ERR: Product doesn't exist.");

	wms::internal::sql::QueryManager query;
	std::unique_ptr<pqxx::connection> conn = query.open_connection();

	std::string sqlfile_str = wms::util::read_sql_from_file("./sql/products/remove_product.sql");
	wms::util::replace_substrings(sqlfile_str, {
		{ "{sku}", this->sku }
	});

	query.execute_query(conn, sqlfile_str, "remove_product");

	query.close_connection(std::move(conn));
}

void wms::products::Product::commit_remove(const std::string& sku) noexcept(false)
{
	if (!wms::util::is_valid_sku(sku))
		throw std::runtime_error("ERR: Invalid SKU format.");

	wms::internal::sql::QueryManager query;
	std::unique_ptr<pqxx::connection> conn = query.open_connection();

	std::string sqlfile_str = wms::util::read_sql_from_file("./sql/products/check_product_exists.sql");
	wms::util::replace_substrings(sqlfile_str, {
		{ "{sku}", sku }
	});

	pqxx::result r = query.execute_query(conn, sqlfile_str, "check_product_exists");
	if (r.size() == 0)
		throw std::runtime_error("ERR: Product doesn't exist.");

	sqlfile_str = wms::util::read_sql_from_file("./sql/products/remove_product.sql");
	wms::util::replace_substrings(sqlfile_str, {
		{ "{sku}", sku }
	});

	query.execute_query(conn, sqlfile_str, "remove_product");

	query.close_connection(std::move(conn));
}
