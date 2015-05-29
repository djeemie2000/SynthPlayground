TEMPLATE = subdirs

CONFIG += ordered
CONFIG += c++11 (Qt5)

SUBDIRS += \
    ../UnitTest \           #a "lib' project
    ../TinyXml2 \           # a 'lib' project
    ../Mongoose \           # a 'lib' project
    ../Utilities \          # a 'lib' project
    ../SynthLib \           # a 'lib' project
    ../TestSynthLib \       # an 'app' project
    ../MidiLib \            # a 'lib' project
    ../JackLib \            # a 'lib' project
    ../AlsaLib \            # a 'lib' project
    ../SerialLib \          # a 'lib' project
    ../CommandStackLib \    # a 'lib' project
    ../TestCommandStackLib \ # an 'app' project
    ../PatchLib \           # a 'lib' project
    ../GuiLib \             # a 'lib' project
    ../ModularLib \         # a 'lib' project
    ../TestModularLib \     # an 'app' project
    ../Scope \              # an  'app' project
    ../JackConnectionTool \ # an  'app' project
    ../JackMidiLoggerTool \ # an  'app' project
    ../AlsaMidiLoggerTool \ # an  'app' project
    ../Serial2AlsaMidiTool \ # an  'app' project
    ../PatchConverterTool \ # an  'app' project
    ../ModularGui \         # an  'app' project
    ../ModularHeadless \    # an  'app' project
    ../ModularWeb           # an  'app' project
