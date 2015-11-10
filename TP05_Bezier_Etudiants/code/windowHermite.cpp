#include "windowHermite.h"

WindowHermite::WindowHermite(QWidget *parent)
    : myGLWidget(60, parent, "Courbe d'hermite")
{
}

void WindowHermite::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void WindowHermite::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
    case Qt::Key_Escape:
        exit(0);
        break;
    }

    update();
}

void WindowHermite::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void WindowHermite::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    hermite(point3(-1,0,0), point3(1,0,0), point3(0,-5,0), point3(0,-5,0));

    glFlush();
}

float WindowHermite::hermite(const point3 &p0, const point3 &p1, const point3 &v0, const point3 &v1)
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
