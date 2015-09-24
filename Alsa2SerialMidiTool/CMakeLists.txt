cmake_minimum_required (VERSION 2.6)
project (Alsa2SerialMidiTool)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../AlsaLib ./../MidiLib)

add_executable(Alsa2SerialMidiTool
    main.cpp)

target_link_libraries(Alsa2SerialMidiTool AlsaLib MidiLib asound)
