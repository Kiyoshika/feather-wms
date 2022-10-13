add_library(wmsmenu 
	BaseMenu.cpp
	AdminMenu.cpp)
target_include_directories(wmsmenu PUBLIC ${FeatherWMS_SOURCE_DIR}/include/client)

add_executable(wmsclient wmsclient.cpp)
target_link_libraries(wmsclient wmsmenu)

