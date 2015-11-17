#-------------------------------------------------
#
# Project created by QtCreator 2015-11-17T09:41:09
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
    lib/struct.cpp \
    windowSurfaceReglee.cpp \
    courbebezier.cpp

HEADERS  += \
    lib/myglwidget.h \
    lib/struct.h \
    windowSurfaceReglee.h \
    courbebezier.h
