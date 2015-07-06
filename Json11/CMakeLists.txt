cmake_minimum_required (VERSION 2.6)
project (Json11)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

add_library(Json11
    json11.cpp
    json11.hpp
)

