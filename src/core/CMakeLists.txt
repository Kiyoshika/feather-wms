add_library(wmsquerymanager QueryManager.cpp)
target_include_directories(wmsquerymanager PUBLIC
	${FeatherWMS_SOURCE_DIR}/include
    ${FeatherWMS_SOURCE_DIR}/include/core)
target_link_libraries(wmsquerymanager pqxx)

add_library(wmsutil Util.cpp)
target_include_directories(wmsutil PUBLIC
	${FeatherWMS_SOURCE_DIR}/include
    ${FeatherWMS_SOURCE_DIR}/include/core)

add_library(wmslocation 
    Locations/PickableLocation/PickableLocation.cpp
    Locations/PickableLocation/PickableLocation_Internal.cpp
	Locations/NonPickableLocation/NonPickableLocation.cpp
	Locations/NonPickableLocation/NonPickableLocation_Internal.cpp
)
target_include_directories(wmslocation PUBLIC 
	${FeatherWMS_SOURCE_DIR}/include
    ${FeatherWMS_SOURCE_DIR}/include/core
	${FeatherWMS_SOURCE_DIR}/include/core/Locations
)
target_link_libraries(wmslocation pqxx wmsutil wmsquerymanager)

