TEMPLATE = subdirs

CONFIG += ordered
CONFIG += c++11 (Qt5)

SUBDIRS += \
    ../UnitTest \   #a "lib' project
    ../SynthLib \        # a "lib' project
    ../TestSynthLib \
    ../GuiLib \ # a 'lib' project
    ../Synth7         # an  "app' project

