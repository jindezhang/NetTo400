#-------------------------------------------------
#
# Project created by QtCreator 2018-10-31T11:01:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetTo400
TEMPLATE = app
RC_ICONS = ./Q7Reader.ico

#QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    tcp.cpp \
    serial.cpp \
    work.cpp \
    dialog.cpp

HEADERS += \
        mainwindow.h \
    tcp.h \
    serial.h \
    mymsg.h \
    work.h \
    dialog.h \
    header.h

FORMS += \
        mainwindow.ui \
    tcp.ui \
    serial.ui \
    dialog.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../log4cxx/bin/msvc2015x64/release/ -llog4cxx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../log4cxx/bin/msvc2015x64/debug/ -llog4cxx

INCLUDEPATH += $$PWD/../../../log4cxx/bin/msvc2015x64/Debug
DEPENDPATH += $$PWD/../../../log4cxx/bin/msvc2015x64/Debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../log4cxx/bin/msvc2015x64/release/liblog4cxx.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../log4cxx/bin/msvc2015x64/debug/liblog4cxx.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../log4cxx/bin/msvc2015x64/release/log4cxx.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../log4cxx/bin/msvc2015x64/debug/log4cxx.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../x64/release/ -llibcommunicate
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../x64/debug/ -llibcommunicate
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../x64/release/ -llibframe
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../x64/debug/ -llibframe
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../x64/release/ -llibnetwork
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../x64/debug/ -llibnetwork
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../x64/release/ -llibtransport
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../x64/debug/ -llibtransport
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../x64/release/ -llibunit
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../x64/debug/ -llibunit


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../x64/release/ -llibcontrol
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../x64/debug/ -llibcontrol

INCLUDEPATH += $$PWD/../Control/libcontrol
INCLUDEPATH += $$PWD/../../../log4cxx/apache-log4cxx-0.10.0/src/main/include
INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../x64/Debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../x64/release/liblibcontrol.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../x64/debug/liblibcontrol.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../x64/release/libcontrol.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../x64/debug/libcontrol.lib

#message($$INCLUDEPATH)
