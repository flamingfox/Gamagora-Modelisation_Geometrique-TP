#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : myGLWidget(60, parent, "TP5 Geometrie")
{
}

void MainWindow::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Initialisation des points de contrôles
    // On choisit de les intialiser selon une ligne
    for (int i = 0; i < Ordre; i++)
    {
        TabPC[i] = point3(i,i,i);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
    case '+':
        if (numPoint < Ordre-1)
            numPoint = numPoint + 1;
        else
            numPoint = 0;
        tx=0;
        ty=0;
        break;
    case '-':
        if (numPoint > 0)
            numPoint = numPoint - 1;
        else
            numPoint = Ordre-1;
        tx=0;
        ty=0;
        break;

    case 'd':
        tx=0.1;
        ty=0;
        break;
    case 'q':
        tx=-0.1;
        ty=0;
        break;
    case 'z':
        ty=0.1;
        tx=0;
        break;
    case 's':
        ty=-0.1;
        tx=0;
        break;
    case Qt::Key_Escape:
        exit(0);
        break;
    default :
        tx=0;
        ty=0;
    }

    update();
}


void MainWindow::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(tx,ty,0.0);


    point3 Ptemp;

    TabPC[numPoint]=TabPC[numPoint]+point3(tx,ty,0);

    // Enveloppe des points de controles
    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (int i =0; i < Ordre; i++)
    {
        glVertex3f(TabPC[i].x, TabPC[i].y, TabPC[i].z);
    }
    glEnd();


    // Affichage du point de controle courant
    // On se déplace ensuite avec + et -
    // ° d'un point de contrôle au suivant (+)
    // ° d'un point de contrôle au précédent (-)
    glColor3f (0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(TabPC[numPoint].x+0.1, TabPC[numPoint].y+0.1, TabPC[numPoint].z);
    glVertex3f(TabPC[numPoint].x+0.1, TabPC[numPoint].y-0.1, TabPC[numPoint].z);
    glVertex3f(TabPC[numPoint].x-0.1, TabPC[numPoint].y-0.1, TabPC[numPoint].z);
    glVertex3f(TabPC[numPoint].x-0.1, TabPC[numPoint].y+0.1, TabPC[numPoint].z);
    glEnd();

    // Dessiner ici la courbe de Bézier.
    // Vous devez avoir implémenté Bernstein précédemment.

    glEnd();
    glFlush();

}
