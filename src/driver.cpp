#include <iostream>
#include "PickableLocation.hpp"

using wms::locations::PickableLocation;

int main()
{
	PickableLocation loc("AVP1", 10, 100, 0, true);
	std::cout << loc.to_string() << "\n";
	return 0;
}
