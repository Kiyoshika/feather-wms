#include <iostream>
#include "PickableLocation.hpp"

using wms::locations::PickableLocation;

int main()
{
	PickableLocation loc("AVP1", 10, 100, 0, true);
	loc.commit_insert();
	return 0;
}
