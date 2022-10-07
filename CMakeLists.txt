cmake_minimum_required(VERSION 3.10)
project(FeatherWMS CXX)

set(CMAKE_CXX_STANDARD 17)
option(CMAKE_BUILD_TYPE Debug) # default build = Debug

# build pqxx dependency (PostgreSQL client for C++)
option(BUILD_TEST OFF) # don't build tests for libpqxx
add_subdirectory(ext/libpqxx)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2")

add_subdirectory(src)
