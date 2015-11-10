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
    glOrtho(-2, 2, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void WindowHermite::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    hermite(point3(-1,0,0), point3(1,0,0), point3(4,4,0), point3(4,4,0));

    glFlush();
}

float WindowHermite::hermite(const point3 &p0, const point3 &p1, const point3 &v0, const point3 &v1)
{
    point3 a = p0*2 - p1*2 + v0 + v1;
    point3 b = p0*(-3) + p1*3 - v0*2 - v1;
    point3 c = v0;
    point3 d = p0;

    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for(float i=1; i<=resolution; i++){
        point3 pU = a*((i-1)/resolution)*((i-1)/resolution)*((i-1)/resolution) +
                b*((i-1)/resolution)*((i-1)/resolution) +
                c*((i-1)/resolution) + d;

        glVertex3f(pU.x, pU.y, pU.z);
    }
    glEnd();
}
