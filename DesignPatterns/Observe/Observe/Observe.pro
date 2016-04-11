TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Subject.cpp \
    Observer.cpp \
    ConCreteObserverA.cpp \
    ConCreteObserverB.cpp \
    ConcreteSubject.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Subject.h \
    Observer.h \
    ConCreteObserverA.h \
    ConCreteObserverB.h \
    ConcreteSubject.h

