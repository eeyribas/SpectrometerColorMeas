QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    colorcalc.cpp \
    utility.cpp \
    spectrometerdata.cpp \
    spectrumdata.cpp \
    datafilter.cpp \
    spectrometermodel.cpp \
    insion.cpp \
    serialport.cpp \
    luminaryvalues.cpp \
    xyzvalues.cpp \
    datapaths.cpp \
    fileoperations.cpp \
    plate.cpp

HEADERS += \
    colorcalc.h \
    utility.h \
    spectrometerdata.h \
    spectrumdata.h \
    datafilter.h \
    spectrometermodel.h \
    insion.h \
    serialport.h \
    luminaryvalues.h \
    standartvalues.h \
    xyzvalues.h \
    datapaths.h \
    fileoperations.h \
    plate.h
