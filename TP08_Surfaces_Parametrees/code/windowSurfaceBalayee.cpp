#include "windowSurfaceBalayee.h"

windowSurfaceBalayee::windowSurfaceBalayee(QWidget *parent)
    : myGLWidget(60, parent, "Surface Balayée")
{
}

void windowSurfaceBalayee::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);


    sr.addPointForme( point3(0,0,0) );
    sr.addPointForme( point3(1,1,0) );
    sr.addPointForme( point3(1,-3,0) );
    sr.addPointForme( point3(-1,-3,0) );
    sr.addPointForme( point3(-1,1,0) );
    sr.addPointForme( point3(0,0,0) );

    sr.addPointPorteuse( point3(0,2,-4) );
    sr.addPointPorteuse( point3(-1,1,-3) );
    sr.addPointPorteuse( point3(0,0,-2) );
    sr.addPointPorteuse( point3(1,-1,-1) );
    sr.addPointPorteuse( point3(0,-2,0) );

}

void windowSurfaceBalayee::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
    case Qt::Key_Escape:
        exit(0);
        break;
    }

    update();
}

void windowSurfaceBalayee::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    //glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, -5, 5);
    glMatrixMode(GL_MODELVIEW);
}

void windowSurfaceBalayee::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    // Dessiner ici la courbe de Bézier.
    // Vous devez avoir implémenté Bernstein précédemment.

    point3 pUor;
    point3 pUtmp;

    glColor3f (0.4, 8.0, 8.0);
    glBegin(GL_TRIANGLES);

    for(float j=0; j<=resolutionPorteuse; j++){
        for(float i=0; i<=resolutionForme; i++){
            if(i!=resolutionForme && j!=resolutionPorteuse){
                pUtmp = sr.calculPu(i/resolutionForme, j/resolutionPorteuse);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);

                pUtmp = sr.calculPu(i/resolutionForme, (j+1)/resolutionPorteuse);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);

                pUtmp = sr.calculPu((i+1)/resolutionForme, j/resolutionPorteuse);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);
            }

            if(i!=0 && j!=0){
                pUtmp = sr.calculPu((i-1)/resolutionForme, j/resolutionPorteuse);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);

                pUtmp = sr.calculPu(i/resolutionForme, j/resolutionPorteuse);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);

                pUtmp = sr.calculPu(i/resolutionForme, (j-1)/resolutionPorteuse);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);
            }
        }
    }
    glEnd();

    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES);

    for(float j=0; j<=resolutionPorteuse; j++){
        for(float i=0; i<=resolutionForme; i++){
            pUor = sr.calculPu(i/resolutionForme, j/resolutionPorteuse);
            if(i!=resolutionForme){
                pUtmp = sr.calculPu((i+1)/resolutionForme, j/resolutionPorteuse);
                glVertex3f(pUor.x, pUor.y, pUor.z);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);
            }

            /*
            if(j!=resolutionPorteuse){
                pUtmp = sr.calculPu(i/resolutionForme, (j+1)/resolutionPorteuse);
                glVertex3f(pUor.x, pUor.y, pUor.z);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);
            }
            */

        }
    }

    glEnd();

    glFlush();
}
