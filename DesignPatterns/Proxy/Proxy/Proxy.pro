TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Subject.cpp \
    ConcreteSubject.cpp \
    ProxySubject.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Subject.h \
    ConcreteSubject.h \
    ProxySubject.h

