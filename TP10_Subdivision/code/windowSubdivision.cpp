#include "WindowSubdivision.h"

WindowSubdivision::WindowSubdivision(QWidget *parent)
    : myGLWidget(60, parent, "Courbe avec subdivision")
{
}

void WindowSubdivision::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    cb.addPoint( point3(-1.5,-0.5,0) );
    cb.addPoint( point3(-1.5,0.5,0) );
    cb.addPoint( point3(-0.5,0.5,0) );
    cb.addPoint( point3(-0.5,1.5,0) );
    cb.addPoint( point3(0.5,1.5,0) );
    cb.addPoint( point3(0.5,0.5,0) );
    cb.addPoint( point3(1.5,0.5,0) );
    cb.addPoint( point3(1.5,-0.5,0) );
    cb.addPoint( point3(0.5,-0.5,0) );
    cb.addPoint( point3(0.5,-1.5,0) );
    cb.addPoint( point3(-0.5,-1.5,0) );
    cb.addPoint( point3(-0.5,-0.5,0) );
}

void WindowSubdivision::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
    case Qt::Key_Escape:
        exit(0);
        break;
    }

    update();
}

void WindowSubdivision::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, -5, 5);
    glMatrixMode(GL_MODELVIEW);
}

void WindowSubdivision::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glColor3f (0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<=cb.getNbPoint(); i++){
        point3 pU = cb[i%cb.getNbPoint()];
        glVertex3f(pU.x-2, pU.y+2, pU.z);
    }
    glEnd();

    Courbe tmp = Courbe::subdivision(cb, 1);

    glColor3f (0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<=tmp.getNbPoint(); i++){
        point3 pU = tmp[i%tmp.getNbPoint()];
        glVertex3f(pU.x+2, pU.y+2, pU.z);
    }
    glEnd();

    tmp = Courbe::subdivision(cb, 2);

    glColor3f (0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<=tmp.getNbPoint(); i++){
        point3 pU = tmp[i%tmp.getNbPoint()];
        glVertex3f(pU.x-2, pU.y-2, pU.z);
    }
    glEnd();

    tmp = Courbe::subdivision(cb, 5);

    glColor3f (0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<=tmp.getNbPoint(); i++){
        point3 pU = tmp[i%tmp.getNbPoint()];
        glVertex3f(pU.x+2, pU.y-2, pU.z);
    }
    glEnd();

    glFlush();
}
