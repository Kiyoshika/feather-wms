# add all SQL files necessary for client into build folder
# LOCATION QUERIES
configure_file(sql/locations/check_location_exists.sql sql/locations/check_location_exists.sql COPYONLY)
configure_file(sql/locations/insert_new_location.sql sql/locations/insert_new_location.sql COPYONLY)
configure_file(sql/locations/update_is_active.sql sql/locations/update_is_active.sql COPYONLY)
configure_file(sql/locations/fetch_location.sql sql/locations/fetch_location.sql COPYONLY)
configure_file(sql/locations/delete_location.sql sql/locations/delete_location.sql COPYONLY)

# PRODUCT QUERIES
configure_file(sql/products/check_product_exists.sql sql/products/check_product_exists.sql COPYONLY)
configure_file(sql/products/insert_new_product.sql sql/products/insert_new_product.sql COPYONLY)
configure_file(sql/products/remove_product.sql sql/products/remove_product.sql COPYONLY)

add_library(wmsmenu 
	Menus/BaseMenu.cpp
	Menus/AdminMenu.cpp
	Menus/ProductMenu.cpp
	Locations/LocationMenu.cpp
	Locations/AddLocation.cpp
	Locations/EditLocation.cpp
	Locations/RemoveLocation.cpp
	Products/AddProduct.cpp
	Products/RemoveProduct.cpp
)

target_include_directories(wmsmenu PUBLIC 
	${FeatherWMS_SOURCE_DIR}/include
	${FeatherWMS_SOURCE_DIR}/include/core
	${FeatherWMS_SOURCE_DIR}/include/client
	${FeatherWMS_SOURCE_DIR}/include/client/Locations
	${FeatherWMS_SOURCE_DIR}/include/client/Products
)
target_link_libraries(wmsmenu wmslocation wmsproduct)

add_executable(wmsclient wmsclient.cpp)
target_link_libraries(wmsclient wmsmenu)

