#ifndef WINDOWSURFACEBALAYEE_H
#define WINDOWSURFACEBALAYEE_H

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
#include "surfacebalayee.h"

class windowSurfaceBalayee : public myGLWidget
{
    surfaceBalayee sr;

public:
    unsigned int resolutionForme = 10, resolutionPorteuse = 10;

    explicit windowSurfaceBalayee(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent( QKeyEvent *keyEvent );

private:
};

#endif // WINDOWSURFACEBALAYEE_H
