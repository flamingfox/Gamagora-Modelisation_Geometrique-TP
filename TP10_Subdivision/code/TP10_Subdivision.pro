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
    lib/struct.cpp \
    courbe.cpp \
    windowSubdivision.cpp

HEADERS  += \    
    lib/myglwidget.h \
    lib/struct.h \
    courbe.h \
    windowSubdivision.h
