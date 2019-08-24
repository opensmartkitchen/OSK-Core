TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread
LIBS += -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs

SOURCES += main.cpp \
    oskgadget.cpp \
    oskdevice.cpp \
    oskcam.cpp \
    oskloadcell.cpp

HEADERS += \
    oskgadget.h \
    oskdevice.h \
    oskcam.h \
    oskloadcell.h
