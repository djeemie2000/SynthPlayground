cmake_minimum_required (VERSION 2.6)
project (PatchLib)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../ModularLib ./../CommandStackLib ./../JackLib ./../Utilities ./../TinyXml2)

add_library(PatchLib
    PatchReader.cpp
    PatchReader.h
    PatchWriter.cpp
    PatchWriter.h
    PatchManager.cpp
    PatchManager.h
)

