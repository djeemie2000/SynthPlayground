cmake_minimum_required (VERSION 2.6)
project (TestModularLib)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../SynthLib ./../SynthLib/Controllers ./../ModularLib/Filters ./../UnitTest)

add_executable(TestModularLib
    main.cpp
    TestPhasorFilter.cpp
    TestMultiStepSequencerFilter.cpp
)

target_link_libraries(TestModularLib ModularLib SynthLib UnitTest)
