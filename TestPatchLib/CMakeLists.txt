cmake_minimum_required (VERSION 2.6)
project (TestPatchLib)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../PatchLib ./../UnitTest)

add_executable(TestPatchLib
    main.cpp
)

target_link_libraries(TestPatchLib PatchLib UnitTest)
