add_library(wmsquerymanager QueryManager.cpp)
target_include_directories(wmsquerymanager PUBLIC
    ${FeatherWMS_SOURCE_DIR}/include)
target_link_libraries(wmsquerymanager pqxx)

add_library(wmsutil Util.cpp)
target_include_directories(wmsutil PUBLIC
    ${FeatherWMS_SOURCE_DIR}/include)

add_library(wmslocation 
    PickableLocation/PickableLocation.cpp
    PickableLocation/PickableLocation_Internal.cpp)
target_include_directories(wmslocation PUBLIC 
    ${FeatherWMS_SOURCE_DIR}/include)
target_link_libraries(wmslocation pqxx wmsutil wmsquerymanager)

add_executable(driver driver.cpp)
target_link_libraries(driver wmslocation)

