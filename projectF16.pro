QT       += core gui

QT       += opengl

QT       += openglwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    f16widget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    f16widget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lopengl32 -lglu32

win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64/' -lOpenGL32
else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64/' -lOpenGL32
else:unix: LIBS += -L'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64/' -lOpenGL32
QT += core gui opengl widgets

win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64/' -lGlU32
else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64/' -lGlU32
else:unix: LIBS += -L'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64/' -lGlU32

INCLUDEPATH += 'C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/um'
DEPENDPATH += 'C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/um'
