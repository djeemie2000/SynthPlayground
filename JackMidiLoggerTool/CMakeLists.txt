cmake_minimum_required (VERSION 2.6)
project (JackMidiLoggerTool)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../JackLib ./../MidiLib ./../ModularLib ./../ModularLib/Modules)
#todo win32 support

add_executable(JackMidiLoggerTool
    main.cpp)

target_link_libraries(JackMidiLoggerTool ModularLib JackLib MidiLib jack)
