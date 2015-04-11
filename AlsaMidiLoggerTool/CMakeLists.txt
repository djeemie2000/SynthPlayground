cmake_minimum_required (VERSION 2.6)
project (AlsaMidiLoggerTool)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../AlsaLib ./../MidiLib)

add_executable(AlsaMidiLoggerTool
    main.cpp)

target_link_libraries(AlsaMidiLoggerTool AlsaLib MidiLib asound)
