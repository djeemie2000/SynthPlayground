cmake_minimum_required (VERSION 2.6)
project (Serial2AlsaMidiTool)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../SerialLib ./../AlsaLib ./../MidiLib ./../SynthLib ./../Utilities)

add_executable(Serial2AlsaMidiTool
    main.cpp)

target_link_libraries(Serial2AlsaMidiTool SerialLib AlsaLib MidiLib asound)
