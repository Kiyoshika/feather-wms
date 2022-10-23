#include "Product.hpp"

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

void wms::products::Product::commit_insert() const noexcept(false)
{
	// TODO: insert product into database
}
