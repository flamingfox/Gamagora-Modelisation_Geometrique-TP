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


    Courbe1.addPoint( point3(-2,-2,0) );
    Courbe1.addPoint( point3(-1,1,0) );
    Courbe1.addPoint( point3(1,1,0) );
    Courbe1.addPoint( point3(2,-2,0) );

    Courbe2.addPoint( point3(2,-2,0) );
    Courbe2.addPoint( point3(3,1,0) );
    Courbe2.addPoint( point3(5,1,0) );
    Courbe2.addPoint( point3(6,-2,0) );
}

void WindowBernsteinDouble::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
    case '+':
        if (numPoint < Courbe1.getDegree())
            numPoint = numPoint + 1;
        else
            numPoint = 0;
        break;
    case '-':
        if (numPoint > 0)
            numPoint = numPoint - 1;
        else
            numPoint = Courbe1.getDegree();
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
    for (int i =0; i < Courbe1.getOrdre(); i++)
    {
        glVertex3f(Courbe1[i].x, Courbe1[i].y, Courbe1[i].z);
    }
    glEnd();

    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (int i =0; i < Courbe2.getOrdre(); i++)
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

    //C0DoubleBezier(Courbe1, Courbe2);
    C1DoubleBezier(Courbe1, Courbe2);

    glFlush();
}

void WindowBernsteinDouble::C0DoubleBezier(CourbeBezier Courbe1, CourbeBezier Courbe2)
{
    glColor3f (0.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for(float i=0; i<=resolution; i++){
        point3 pU = Courbe1.calculPu( i/resolution );
        glVertex3f(pU.x, pU.y, pU.z);
    }
    glEnd();

    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    if( Courbe1[Courbe1.getOrdre()-1].x != Courbe2[0].x || Courbe1[Courbe1.getOrdre()-1].y != Courbe2[0].y || Courbe1[Courbe1.getOrdre()-1].z != Courbe2[0].z ){

        point3 v0 = Courbe1[Courbe1.getOrdre()-1] - Courbe1[Courbe1.getOrdre()-2];
        point3 v1 = Courbe2[1] - Courbe2[0];

        hermite(Courbe1[Courbe1.getOrdre()-1], Courbe2[0], v0, v1, resolution);
    }
    glEnd();

    glColor3f (1.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for(float i=0; i<=resolution; i++){
        point3 pU = Courbe2.calculPu( i/resolution );
        glVertex3f(pU.x, pU.y, pU.z);
    }
    glEnd();

}

void WindowBernsteinDouble::C1DoubleBezier(CourbeBezier Courbe1, CourbeBezier Courbe2)
{
    point3 tangente = Courbe2[1] - Courbe1[Courbe1.getOrdre()-2];
    tangente = tangente.normalize();

    float dCourbe1 = (Courbe1[Courbe1.getOrdre()-2] - Courbe1[Courbe1.getOrdre()-1]).dotProduct(tangente);
    float dCourbe2 = (Courbe2[1] - Courbe2[0]).dotProduct(tangente);

    CourbeBezier Courbe1bis(Courbe1);
    CourbeBezier Courbe2bis(Courbe2);

    Courbe1bis[Courbe1.getOrdre()-2] = Courbe1[Courbe1.getOrdre()-1] + tangente*dCourbe1;
    Courbe2bis[1] = Courbe2[0] + tangente*dCourbe2;

    glColor3f (0.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for(float i=0; i<=resolution; i++){
        point3 pU = Courbe1bis.calculPu( i/resolution );
        glVertex3f(pU.x, pU.y, pU.z);
    }
    glEnd();

    glColor3f (1.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for(float i=0; i<=resolution; i++){
        point3 pU = Courbe2bis.calculPu( i/resolution );
        glVertex3f(pU.x, pU.y, pU.z);
    }
    glEnd();

    glColor3f (1.0, 0.0, 1.0);
    glBegin(GL_LINES);

    glVertex3f(Courbe1bis[Courbe1bis.getOrdre()-1].x, Courbe1bis[Courbe1bis.getOrdre()-1].y, Courbe1bis[Courbe1bis.getOrdre()-1].z);
    glVertex3f(Courbe1bis[Courbe1bis.getOrdre()-2].x, Courbe1bis[Courbe1bis.getOrdre()-2].y, Courbe1bis[Courbe1bis.getOrdre()-2].z);

    glVertex3f(Courbe2bis[0].x, Courbe2bis[0].y, Courbe2bis[0].z);
    glVertex3f(Courbe2bis[1].x, Courbe2bis[1].y, Courbe2bis[1].z);

    glEnd();
}

float WindowBernsteinDouble::hermite(const point3 &p0, const point3 &p1, const point3 &v0, const point3 &v1, const int &resolution)
{
    point3 a = p0*2-p1*2+v0+v1;
    point3 b = p0*(-3)+p1*3-v0*2-v1;
    point3 c = v0;
    point3 d = p0;

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
}
