cmake_minimum_required (VERSION 2.6)
project (Utilities)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

add_library(Utilities
    ClockUtilities.h
    ContinuousThreadRunner.h
    PeriodicThreadRunner.h
    FileSystemHelpers.cpp
    FileSystemHelpers.h
)

