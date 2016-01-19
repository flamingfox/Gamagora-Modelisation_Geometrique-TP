#ifndef WINDOWSURFACECASTLEJAU_H
#define WINDOWSURFACECASTLEJAU_H

#include "lib/myGLWidget.h"
#include <QImage>

/*
 *	Tableau des points permettant de gérer les points de controles
 * On sélectionne le point en se déplaçant avec + et -, ...
 * On sélectionne ensuite si on veut faire monter, descendre amener vers la gauche ou la droite le point.
 *   d : translation à droite
 *   q : à gauche
 *   z : en haut
 *   s : en bas
 *
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "lib/struct.h"
#include "surfacecastlejau.h"

class windowSurfaceCastlejau : public myGLWidget
{
    SurfaceCastlejau sr;

public:
    unsigned int resolution = 10;

    explicit windowSurfaceCastlejau(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent( QKeyEvent *keyEvent );

private:
};

#endif // WINDOWSURFACECASTLEJAU_H
