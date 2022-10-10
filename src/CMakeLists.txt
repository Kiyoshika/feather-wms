add_subdirectory(client)
add_subdirectory(core)

add_executable(driver driver.cpp)
target_link_libraries(driver wmslocation)