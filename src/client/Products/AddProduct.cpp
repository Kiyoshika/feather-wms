#include "AddProduct.hpp"
#include "Product.hpp"
#include "Util.hpp"


wms::menu::products::AddProduct::AddProduct() noexcept(false)
{
	this->clear_screen();
	
	std::string sku;
	std::cout << "Enter SKU# (max length: 30): ";
	std::cin >> sku;

	if (sku == "F1")
		return;

	if (!wms::util::is_valid_sku(sku))
		throw std::runtime_error("ERR: Invalid SKU format.");

	std::string upc;
	std::cout << "\nEnter UPC (max length: 30): ";
	std::cin >> upc;

	if (upc == "F1")
		return;

	if (!wms::util::is_valid_upc(upc))
		throw std::runtime_error("ERR: Invalid UPC format.");

	std::string product_name;
	std::cout << "\nEnter product name (max length: 50): ";
	std::getline(std::cin, product_name); // consume any previous newline characters
	std::getline(std::cin, product_name);

	if (product_name == "F1")
		return;

	if (!wms::util::is_valid_product_name(product_name))
		throw std::runtime_error("ERR: Invalid product name format.");

	std::string contains_description_str;
	while ( contains_description_str != "y" &&
			contains_description_str != "Y" &&
			contains_description_str != "n" &&
			contains_description_str != "N")
	{
		std::cout << "\nDoes product contain description? (y/n): ";
		std::cin >> contains_description_str;
		if (contains_description_str == "F1")
			return;
	}

	std::string product_description;
	if (contains_description_str == "y" || contains_description_str == "Y")
	{
		std::cout << "\nEnter product description (max length: 300): ";
		std::getline(std::cin, product_description); // consume any previous newline characters
		std::getline(std::cin, product_description);
		if (!wms::util::is_valid_product_description(product_description))
			throw std::runtime_error("ERR: Invalid product description format.");
	}

	std::string item_cost_str;
	std::cout << "\nEnter item cost (positive numeric): ";
	std::cin >> item_cost_str;

	if (item_cost_str == "F1")
		return;

	if (!wms::util::is_non_negative_double(item_cost_str))
		throw std::runtime_error("ERR: Invalid item cost format.");

	double item_cost = std::stod(item_cost_str);

	std::string listing_price_str;
	std::cout << "\nEnter item listing price (positive numeric): ";
	std::cin >> listing_price_str;

	if (listing_price_str == "F1")
		return;

	if (!wms::util::is_non_negative_double(listing_price_str))
		throw std::runtime_error("ERR: Invalid listing price format");

	double listing_price = std::stod(listing_price_str);

	std::string item_length_str;
	std::cout << "\nEnter item length (positive numeric): ";
	std::cin >> item_length_str;

	if (item_length_str == "F1")
		return;

	if (!wms::util::is_non_negative_double(item_length_str))
		throw std::runtime_error("ERR: Invalid item length format.");

	double item_length = std::stod(item_length_str);

	std::string item_width_str;
	std::cout << "\nEnter item width (positive numeric): ";
	std::cin >> item_width_str;

	if (item_width_str == "F1")
		return;

	if (!wms::util::is_non_negative_double(item_width_str))
		throw std::runtime_error("ERR: Invalid item width format.");

	double item_width = std::stod(item_width_str);

	std::string item_height_str;
	std::cout << "\nEnter item height (positive numeric): ";
	std::cin >> item_height_str;

	if (item_height_str == "F1")
		return;

	if (!wms::util::is_non_negative_double(item_height_str))
		throw std::runtime_error("ERR: Invalid item height format.");

	double item_height = std::stod(item_height_str);

	std::string item_weight_str;
	std::cout << "\nEnter item weight (positive numeric): ";
	std::cin >> item_weight_str;

	if (item_weight_str == "F1")
		return;

	if (!wms::util::is_non_negative_double(item_weight_str))
		throw std::runtime_error("ERR: Invalid item weight format.");

	double item_weight = std::stod(item_weight_str);

	std::string is_active_str;
	bool is_active = false;
	while ( is_active_str != "y" &&
			is_active_str != "Y" &&
			is_active_str != "n" &&
			is_active_str != "N")
	{
		std::cout << "\nIs item active? (y/n): ";
		std::cin >> is_active_str;

		if (is_active_str == "F1")
			return;
	}

	if (is_active_str == "y" || is_active_str == "Y")
		is_active = true;

	wms::products::Product p(
		sku,
		upc,
		product_name,
		product_description,
		item_cost,
		listing_price,
		item_length,
		item_width,
		item_height,
		item_weight,
		is_active);

	p.commit_insert();
	
}
