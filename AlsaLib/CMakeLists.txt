cmake_minimum_required (VERSION 2.6)
project (AlsaLib)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../SynthLib ./../MidiLib ./../Utilities)

add_library(AlsaLib
    AlsaMidiInput.cpp
    AlsaMidiOutput.cpp
    AlsaMidiInput.h
    AlsaMidiOutput.h)

