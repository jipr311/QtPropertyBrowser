TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += c++11

include(../../src/qtpropertybrowser.pri)
# Input
SOURCES += main.cpp
RESOURCES += demo.qrc
