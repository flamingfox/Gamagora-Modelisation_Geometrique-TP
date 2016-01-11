TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    modele/voxel.cpp \
    geometrie/vector3d.cpp \
    geometrie/sphere.cpp \
    modele/voxelmanager.cpp \
    import_export/objmanager.cpp \
    modele/mesh.cpp

HEADERS += \
    modele/voxel.h \
    geometrie/vector3d.h \
    geometrie/sphere.h \
    modele/voxelmanager.h \
    import_export/objmanager.h \
    modele/mesh.h

