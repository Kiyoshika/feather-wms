# add all SQL files necessary for client into build folder
configure_file(sql/locations/check_location_exists.sql sql/locations/check_location_exists.sql COPYONLY)
configure_file(sql/locations/insert_new_location.sql sql/locations/insert_new_location.sql COPYONLY)

add_library(wmsmenu 
	BaseMenu.cpp
	AdminMenu.cpp
	Locations/AddLocation.cpp
)

target_include_directories(wmsmenu PUBLIC 
	${FeatherWMS_SOURCE_DIR}/include
	${FeatherWMS_SOURCE_DIR}/include/core
	${FeatherWMS_SOURCE_DIR}/include/client
	${FeatherWMS_SOURCE_DIR}/include/client/Locations
)
target_link_libraries(wmsmenu wmslocation)

add_executable(wmsclient wmsclient.cpp)
target_link_libraries(wmsclient wmsmenu)

