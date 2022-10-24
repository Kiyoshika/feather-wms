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

	static std::unique_ptr<Product> fetch_product(const std::string& sku) noexcept(false);

	void commit_insert() const noexcept(false);

	void commit_remove() const noexcept(false);

	static void commit_remove(const std::string& sku) noexcept(false);

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

	bool check_product_exists() const noexcept(false);

}; // class Product
}; // namespace products
}; // namespace wms
#endif
