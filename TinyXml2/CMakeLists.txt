cmake_minimum_required (VERSION 2.6)
project (TinyXml2)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

add_library(TinyXml2
    tinyxml2.cpp
    tinyxml2.h)

