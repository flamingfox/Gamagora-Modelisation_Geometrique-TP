#include "windowBernsteinSimple.h"

WindowBernsteinSimple::WindowBernsteinSimple(QWidget *parent)
    : myGLWidget(60, parent, "Courbe de Bezier (Bernstein simple)")
{
}

void WindowBernsteinSimple::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Initialisation des points de contrôles
    // On choisit de les intialiser selon une ligne
    /*for (int i = 0; i < Ordre; i++)
    {
        TabPC[i] = point3(i,i,i);
    }*/


    cb.addPoint( point3(-2,-2,0) );
    cb.addPoint( point3(-1,1,0) );
    cb.addPoint( point3(1,1,0) );
    cb.addPoint( point3(2,-2,0) );
}

void WindowBernsteinSimple::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
    case '+':
        if (numPoint < cb.getDegree())
            numPoint = numPoint + 1;
        else
            numPoint = 0;
        break;
    case '-':
        if (numPoint > 0)
            numPoint = numPoint - 1;
        else
            numPoint = cb.getDegree();
        break;

    case Qt::Key_D :
        cb[numPoint].x += 0.1;
        cb[numPoint].y += 0;
        break;
    case Qt::Key_Q:
        cb[numPoint].x -= 0.1;
        cb[numPoint].y += 0;
        break;
    case Qt::Key_Z:
        cb[numPoint].x += 0;
        cb[numPoint].y += 0.1;
        break;
    case Qt::Key_S:
        cb[numPoint].x += 0;
        cb[numPoint].y -= 0.1;
        break;
    case Qt::Key_Escape:
        exit(0);
        break;
    }

    update();
}

void WindowBernsteinSimple::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, -5, 5);
    glMatrixMode(GL_MODELVIEW);
}

void WindowBernsteinSimple::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    // Enveloppe des points de controles
    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (int i =0; i < cb.getOrdre(); i++)
    {
        glVertex3f(cb[i].x, cb[i].y, cb[i].z);
    }
    glEnd();


    // Affichage du point de controle courant
    // On se déplace ensuite avec + et -
    // ° d'un point de contrôle au suivant (+)
    // ° d'un point de contrôle au précédent (-)
    glColor3f (0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(cb[numPoint].x+0.1, cb[numPoint].y+0.1, cb[numPoint].z);
    glVertex3f(cb[numPoint].x+0.1, cb[numPoint].y-0.1, cb[numPoint].z);
    glVertex3f(cb[numPoint].x-0.1, cb[numPoint].y-0.1, cb[numPoint].z);
    glVertex3f(cb[numPoint].x-0.1, cb[numPoint].y+0.1, cb[numPoint].z);
    glEnd();

    // Dessiner ici la courbe de Bézier.
    // Vous devez avoir implémenté Bernstein précédemment.
    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);

    for(float i=0; i<=resolution; i++){
        point3 pU = cb.calculPu(i/resolution);
        glVertex3f(pU.x, pU.y, pU.z);
    }

    glEnd();
    glFlush();
}
