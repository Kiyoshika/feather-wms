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

// TODO: implement getters

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
