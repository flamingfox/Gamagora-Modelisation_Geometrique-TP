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


    TabPC[0] = point3(-2,-2,0);
    TabPC[1] = point3(-1,1,0);
    TabPC[2] = point3(1,1,0);
    TabPC[3] = point3(2,-2,0);
}

void WindowBernsteinSimple::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
    case '+':
        if (numPoint < Ordre-1)
            numPoint = numPoint + 1;
        else
            numPoint = 0;
        break;
    case '-':
        if (numPoint > 0)
            numPoint = numPoint - 1;
        else
            numPoint = Ordre-1;
        break;

    case Qt::Key_D :
        TabPC[numPoint].x += 0.1;
        TabPC[numPoint].y += 0;
        break;
    case Qt::Key_Q:
        TabPC[numPoint].x -= 0.1;
        TabPC[numPoint].y += 0;
        break;
    case Qt::Key_Z:
        TabPC[numPoint].x += 0;
        TabPC[numPoint].y += 0.1;
        break;
    case Qt::Key_S:
        TabPC[numPoint].x += 0;
        TabPC[numPoint].y -= 0.1;
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
    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);

    for(float i=0; i<=resolution; i++){
        point3 pU;

        for(int j=0; j< nbPointControle; j++){
            pU = pU + TabPC[j]*Bernstein(j, nbPointControle-1, i/resolution);
        }

        glVertex3f(pU.x, pU.y, pU.z);
    }

    glEnd();
    glFlush();
}

float WindowBernsteinSimple::fact(const int n)
{
    float retour = 1;
    for(int i=n; i>0; i--){
        retour *= i;
    }
    return retour;
}

float WindowBernsteinSimple::Bernstein(int i, int n, float t)
{
    return fact(n) / (fact(i)*fact(n-i)) * powf(t, i) * powf(1-t, n-i);
}
