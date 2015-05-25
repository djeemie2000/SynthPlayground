cmake_minimum_required (VERSION 2.6)
project (PatchConverterTool)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../JackLib ./../PatchLib ./../CommandStackLib ./../SynthLib ./../SynthLib/Granular ./../ModularLib ./../ModularLib/Modules ./../ModularLib/Filters ./../TinyXml2)
#todo win32 support

add_executable(PatchConverterTool
    main.cpp
)

target_link_libraries(PatchConverterTool ModularLib SynthLib MidiLib PatchLib JackLib Utilities CommandStackLib TinyXml2 jack)
