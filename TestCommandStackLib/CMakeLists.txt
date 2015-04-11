cmake_minimum_required (VERSION 2.6)
project (TestCommandStackLib)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../CommandStackLib ./../UnitTest)

add_executable(TestCommandStackLib
    main.cpp
    TestCommandStackDistributor.cpp
    TestCommandStackItem.cpp)

target_link_libraries(TestCommandStackLib CommandStackLib UnitTest)
