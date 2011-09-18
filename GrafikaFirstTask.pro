#-------------------------------------------------
#
# Project created by QtCreator 2011-09-18T13:17:43
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = GrafikaFirstTask

TEMPLATE = app


SOURCES += main.cpp


QT       += core gui

LIBS += -lopengl32 -lglu32# -glut32

INCLUDEPATH = C:/glut-3.5/include
LIBS += C:/glut-3.7.6-bin/glut32.lib

OTHER_FILES += \
    CurrentView.jpg \
    59.png \
    CurrentView.png








