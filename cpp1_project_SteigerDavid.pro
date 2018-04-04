TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    converter.cpp \
    menu.cpp \
    txt_parser.cpp \
    xml_parser.cpp

HEADERS += \
    convert.h \
    header.h \
    scan.h \
    token.h
