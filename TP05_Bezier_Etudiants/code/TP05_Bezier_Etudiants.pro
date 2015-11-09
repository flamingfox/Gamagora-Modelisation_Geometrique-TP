#-------------------------------------------------
#
# Project created by QtCreator 2015-11-09T07:42:04
#
#-------------------------------------------------

QT       += core gui
QT += opengl

LIBS += -lopengl32 -lglu32

CONFIG  += c++11



TARGET = TP05_Bezier_Etudiants
TEMPLATE = app


SOURCES += main.cpp\
    lib/myglwidget.cpp \
    mainwindow.cpp \
    lib/struct.cpp

HEADERS  += \
    mainwindow.h \
    lib/myglwidget.h \
    lib/struct.h
