TEMPLATE = subdirs

CONFIG += ordered
CONFIG += c++11 (Qt5)

SUBDIRS += \
    ../UnitTest \   #a "lib" project
    ../SynthLib \        # a "lib" project
    ../TestSynthLib \
    ../Synth7         # an  "app" project

