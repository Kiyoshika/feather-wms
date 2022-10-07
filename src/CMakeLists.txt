add_library(location PickableLocation.cpp)
target_include_directories(location PUBLIC ${FeatherWMS_SOURCE_DIR}/include)

add_executable(driver driver.cpp)
target_link_libraries(driver location)

