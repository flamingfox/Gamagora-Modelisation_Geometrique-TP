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

class WindowBernsteinDouble : public myGLWidget
{

    #define nbPointControle 4
    // Tableau des points de contrôles en global ...
    point3 Courbe1[nbPointControle];
    point3 Courbe2[nbPointControle];
    // Ordre de la courbre  : Ordre
    // Degré de la courbe = Ordre - 1
    int Ordre = nbPointControle;

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

    void Bezier(point3 Courbe[], const int &nbPoint, const int& resolution);
    void C1DoubleBezier(point3 Courbe1[], point3 Courbe2[], const int &nbPoint1, const int &nbPoint2, const int& resolution);

    // Fonction Factorielle
    float fact(int n);
    float Bernstein(int i, int n, float t);

    float hermite(const point3& p0, const point3& p1, const point3& v0, const point3& v1, const int &resolution);
};

#endif // WINDOWBERNSTEINDOUBLE_H
