#ifndef WINDOWBERNSTEINDOUBLE_H
#define WINDOWBERNSTEINDOUBLE_H

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
#include "courbebezier.h"

class WindowBernsteinDouble : public myGLWidget
{

    #define nbPointControle 4
    // Tableau des points de contrôles en global ...
    CourbeBezier Courbe1;
    CourbeBezier Courbe2;

    // Point de controle selectionné
    int numPoint = 0;

public:
    unsigned int resolution = 10;

    explicit WindowBernsteinDouble(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent( QKeyEvent *keyEvent );

private:
    void C0DoubleBezier(CourbeBezier Courbe1, CourbeBezier Courbe2);
    void C1DoubleBezier(CourbeBezier Courbe1, CourbeBezier Courbe2);

    float hermite(const point3& p0, const point3& p1, const point3& v0, const point3& v1, const int &resolution);
};

#endif // WINDOWBERNSTEINDOUBLE_H
