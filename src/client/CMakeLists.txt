# add all SQL files necessary for client into build folder
configure_file(sql/locations/check_location_exists.sql sql/locations/check_location_exists.sql COPYONLY)
configure_file(sql/locations/insert_new_location.sql sql/locations/insert_new_location.sql COPYONLY)
configure_file(sql/locations/update_is_active.sql sql/locations/update_is_active.sql COPYONLY)
configure_file(sql/locations/fetch_location.sql sql/locations/fetch_location.sql COPYONLY)
configure_file(sql/locations/delete_location.sql sql/locations/delete_location.sql COPYONLY)

add_library(wmsmenu 
	BaseMenu.cpp
	AdminMenu.cpp
	Locations/LocationMenu.cpp
	Locations/AddLocation.cpp
	Locations/EditLocation.cpp
	Locations/RemoveLocation.cpp
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

