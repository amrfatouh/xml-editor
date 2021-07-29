QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    check.cpp \
    classes.cpp \
    compressor.cpp \
    correction.cpp \
    main.cpp \
    mainwindow.cpp \
    minifier.cpp \
    myhighlighter.cpp \
    parsing.cpp \
    prettifying.cpp \
    xml_to_json.cpp




HEADERS += \
    check.h \
    correction.h \
    mainwindow.h \
    minifier.h \
    myhighlighter.h \
    parsing.h \
    xml_to_json.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
