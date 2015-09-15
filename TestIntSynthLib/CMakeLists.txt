cmake_minimum_required (VERSION 2.6)
project (TestIntSynthLib)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../IntSynthLib ./../UnitTest)

add_executable(TestIntSynthLib
    main.cpp
    TestIntOnePoleFilter.cpp
    TestIntCombinors.cpp
    TestIntOperators.cpp
    TestIntPhaseGenerator.cpp
    TestIntCombinedOperator.cpp
)

target_link_libraries(TestIntSynthLib IntSynthLib UnitTest)
