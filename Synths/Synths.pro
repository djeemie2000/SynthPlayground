TEMPLATE = subdirs

CONFIG += ordered
CONFIG += c++11 (Qt5)

SUBDIRS += \
    ../UnitTest \   #a "lib' project
    ../SynthLib \        # a 'lib' project
    ../TestSynthLib \ # an 'app' project
    ../AlsaMidiLib \ # a 'lib' project
    ../GuiLib \ # a 'lib' project
    ../Synth7  \        # an  'app' project
    ../Synth8         # an  'app' project

