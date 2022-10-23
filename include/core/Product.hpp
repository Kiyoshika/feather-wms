#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <memory>
#include <pqxx/pqxx>

namespace wms
{
namespace products
{
class Product
{
	public:
	Product(
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
		const bool is_active) noexcept(true);

	std::string get_sku() const noexcept(true);

	std::string get_upc() const noexcept(true);

	std::string get_name() const noexcept(true);

	std::string get_description() const noexcept(true);

	double get_item_cost() const noexcept(true);

	double get_listing_price() const noexcept(true);

	double get_length() const noexcept(true);

	double get_width() const noexcept(true);

	double get_height() const noexcept(true);

	double get_weight() const noexcept(true);

	bool check_is_active() const noexcept(true);

	void commit_insert() const noexcept(false);

	private:
	std::string sku;
	std::string upc;
	std::string name;
	std::string description;
	double item_cost;
	double listing_price;
	double length;
	double width;
	double height;
	double weight;
	bool is_active;

}; // class Product
}; // namespace products
}; // namespace wms
#endif
