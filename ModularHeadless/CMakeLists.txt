cmake_minimum_required (VERSION 2.6)
project (ModularHeadLess)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../JackLib ./../MidiLib ./../CommandStackLib ./../PatchLib ./../SynthLib ./../SynthLib/Granular ./../ModularLib ./../ModularLib/Modules ./../ModularLib/Filters ./../TinyXml2)
#todo win32 support

add_executable(ModularHeadLess
    main.cpp
    ModularHeadlessController.cpp
    ModularHeadlessController.h
)

target_link_libraries(ModularHeadLess ModularLib SynthLib JackLib MidiLib CommandStackLib PatchLib Utilities TinyXml2 jack)
