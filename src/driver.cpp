#include <iostream>
#include "PickableLocation.hpp"

using wms::locations::PickableLocation;

int main()
{
	PickableLocation loc("AVP1", 10, 100, 0, true);

	try
	{
		loc.commit_insert();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
