cmake_minimum_required (VERSION 2.6)
project (JackConnectionTool)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../JackLib)
#todo win32 support

add_executable(JackConnectionTool
    main.cpp)

target_link_libraries(JackConnectionTool JackLib jack)
