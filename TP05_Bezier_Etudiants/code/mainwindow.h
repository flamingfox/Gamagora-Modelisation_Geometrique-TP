#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

class MainWindow : public myGLWidget
{    
    float tx=-5.0;
    float ty=-5.0;

    // Tableau des points de contrôles en global ...
    point3 TabPC[10];
    // Ordre de la courbre  : Ordre
    // Degré de la courbe = Ordre - 1
    int Ordre = 10;

    // Point de controle selectionné
    int numPoint = 0;

public:
    explicit MainWindow(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent( QKeyEvent *keyEvent );

private:
    // Fonction Factorielle
    float fact(int n);

    float Bernstein(int i, int n, float t);
};

#endif // MAINWINDOW_H
