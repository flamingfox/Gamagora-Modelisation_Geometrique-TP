#include "windowBernsteinDouble.h"

WindowBernsteinDouble::WindowBernsteinDouble(QWidget *parent)
    : myGLWidget(60, parent, "Courbe de Bezier (Bernstein double)")
{
}

void WindowBernsteinDouble::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Initialisation des points de contrôles
    // On choisit de les intialiser selon une ligne
    /*for (int i = 0; i < Ordre; i++)
    {
        TabPC[i] = point3(i,i,i);
    }*/


    Courbe1[0] = point3(-2,-2,0);
    Courbe1[1] = point3(-1,1,0);
    Courbe1[2] = point3(1,1,0);
    Courbe1[3] = point3(2,-2,0);

    Courbe2[0] = point3(3,-2,0);
    Courbe2[1] = point3(4,1,0);
    Courbe2[2] = point3(6,1,0);
    Courbe2[3] = point3(7,-2,0);
}

void WindowBernsteinDouble::keyPressEvent(QKeyEvent *keyEvent)
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
        Courbe1[numPoint].x += 0.1;
        Courbe1[numPoint].y += 0;
        break;
    case Qt::Key_Q:
        Courbe1[numPoint].x -= 0.1;
        Courbe1[numPoint].y += 0;
        break;
    case Qt::Key_Z:
        Courbe1[numPoint].x += 0;
        Courbe1[numPoint].y += 0.1;
        break;
    case Qt::Key_S:
        Courbe1[numPoint].x += 0;
        Courbe1[numPoint].y -= 0.1;
        break;
    case Qt::Key_Escape:
        exit(0);
        break;
    }

    update();
}

void WindowBernsteinDouble::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4, 8, -4, 4, -4, 8);
    glMatrixMode(GL_MODELVIEW);
}

void WindowBernsteinDouble::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    // Enveloppe des points de controles
    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (int i =0; i < Ordre; i++)
    {
        glVertex3f(Courbe1[i].x, Courbe1[i].y, Courbe1[i].z);
    }
    glEnd();

    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (int i =0; i < Ordre; i++)
    {
        glVertex3f(Courbe2[i].x, Courbe2[i].y, Courbe2[i].z);
    }
    glEnd();


    // Affichage du point de controle courant
    // On se déplace ensuite avec + et -
    // ° d'un point de contrôle au suivant (+)
    // ° d'un point de contrôle au précédent (-)
    glColor3f (0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(Courbe1[numPoint].x+0.1, Courbe1[numPoint].y+0.1, Courbe1[numPoint].z);
    glVertex3f(Courbe1[numPoint].x+0.1, Courbe1[numPoint].y-0.1, Courbe1[numPoint].z);
    glVertex3f(Courbe1[numPoint].x-0.1, Courbe1[numPoint].y-0.1, Courbe1[numPoint].z);
    glVertex3f(Courbe1[numPoint].x-0.1, Courbe1[numPoint].y+0.1, Courbe1[numPoint].z);
    glEnd();

    // Dessiner ici la courbe de Bézier.
    // Vous devez avoir implémenté Bernstein précédemment.
    glColor3f (0.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    Bezier(Courbe1, nbPointControle, resolution);
    glEnd();

    glColor3f (1.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    Bezier(Courbe2, nbPointControle, resolution);
    glEnd();

    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    C1DoubleBezier(Courbe1, Courbe2, nbPointControle, nbPointControle, resolution);
    glEnd();

    glFlush();
}

void WindowBernsteinDouble::Bezier(point3 Courbe[], const int &nbPoint, const int &resolution)
{
    for(float i=0; i<=resolution; i++){
        point3 pU;
        for(int j=0; j< nbPoint; j++){
            pU = pU + Courbe[j]*Bernstein(j, nbPoint-1, i/resolution);
        }
        glVertex3f(pU.x, pU.y, pU.z);
    }
}

void WindowBernsteinDouble::C1DoubleBezier(point3 Courbe1[], point3 Courbe2[], const int &nbPoint1, const int &nbPoint2, const int &resolution)
{
    if( Courbe1[nbPoint1-1].x != Courbe2[0].x && Courbe1[nbPoint1-1].y != Courbe2[0].y && Courbe1[nbPoint1-1].z != Courbe2[0].z ){

        point3 v0 = Courbe1[nbPoint1-1] - Courbe1[nbPoint1-2];
        point3 v1 = Courbe2[1] - Courbe2[0];

        //v0 = v0.normalize();
        //v1 = v1.normalize();

        hermite(Courbe1[nbPoint1-1], Courbe2[0], v0, v1, resolution);
    }
}

float WindowBernsteinDouble::fact(const int n)
{
    float retour = 1;
    for(int i=n; i>0; i--){
        retour *= i;
    }
    return retour;
}

float WindowBernsteinDouble::Bernstein(int i, int n, float t)
{
    return fact(n) / (fact(i)*fact(n-i)) * powf(t, i) * powf(1-t, n-i);
}

float WindowBernsteinDouble::hermite(const point3 &p0, const point3 &p1, const point3 &v0, const point3 &v1, const int &resolution)
{
    point3 a = p0*2-p1*2+v0+v1;
    point3 b = p0*(-3)+p1*3-v0*2-v1;
    point3 c = v0;
    point3 d = p0;

    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for(float i=1; i<=resolution; i++){
        point3 pU0 = a*((i-1)/resolution)*((i-1)/resolution)*((i-1)/resolution) +
                b*((i-1)/resolution)*((i-1)/resolution) +
                c*((i-1)/resolution) + d;

        point3 pU1 = a*(i/resolution)*(i/resolution)*(i/resolution) +
                b*(i/resolution)*(i/resolution) +
                c*(i/resolution) + d;

        glVertex3f(pU0.x, pU0.y, pU0.z);
        glVertex3f(pU1.x, pU1.y, pU1.z);
    }
    glEnd();
}
