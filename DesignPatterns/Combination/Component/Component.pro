TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Component.cpp \
    Leaf.cpp \
    Composite.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Component.h \
    Leaf.h \
    Composite.h

