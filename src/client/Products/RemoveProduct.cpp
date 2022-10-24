#include "RemoveProduct.hpp"
#include "Product.hpp"
#include "Util.hpp"

wms::menu::products::RemoveProduct::RemoveProduct() noexcept(false)
{
	this->clear_screen();

	std::string sku;
	std::cout << "Enter SKU# (max length: 30): ";
	std::cin >> sku;

	if (sku == "F1")
		return;

	// will throw on failure
	wms::products::Product::commit_remove(sku);
}
