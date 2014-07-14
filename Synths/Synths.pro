TEMPLATE = subdirs

CONFIG += ordered
CONFIG += c++11 (Qt5)

SUBDIRS += \
    ../UnitTest \           #a "lib' project
    ../TinyXml2 \           # a 'lib' project
    ../SynthLib \           # a 'lib' project
    ../TestSynthLib \       # an 'app' project
    ../MidiLib \        # a 'lib' project
    ../JackLib \            # a 'lib' project
    ../CommandStackLib \    # a 'lib' project
    ../TestCommandStackLib \ # an 'app' project
    ../GuiLib \             # a 'lib' project
    #../Synth7  \           # an  'app' project
    ../Synth8 \             # an  'app' project
    ../Synth9 \             # an  'app' project
    ../Scope \              # an  'app' project
    ../Synth10              # an  'app' project
