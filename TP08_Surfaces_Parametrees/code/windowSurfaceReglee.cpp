#include "windowSurfaceReglee.h"

windowSurfaceReglee::windowSurfaceReglee(QWidget *parent)
    : myGLWidget(60, parent, "Surface réglée")
{
}

void windowSurfaceReglee::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);


    sr.addPointForme( point3(1,2,0) );
    sr.addPointForme( point3(0,0,0) );
    sr.addPointForme( point3(1,-2,0) );

    sr.addPointPorteuse( point3(-2,0,0) );
    sr.addPointPorteuse( point3(0,1,0) );
    sr.addPointPorteuse( point3(2,0,0) );



    /*
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
    */
}

void windowSurfaceReglee::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
    case Qt::Key_Escape:
        exit(0);
        break;
    }

    update();
}

void windowSurfaceReglee::resizeGL(int width, int height)
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

void windowSurfaceReglee::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    // Dessiner ici la courbe de Bézier.
    // Vous devez avoir implémenté Bernstein précédemment.

    point3 pUor;
    point3 pUtmp;

    glColor3f (0.4, 8.0, 8.0);
    glBegin(GL_TRIANGLES);

    for(float j=0; j<=resolution; j++){
        for(float i=0; i<=resolution; i++){
            if(i!=resolution && j!=resolution){
                pUtmp = sr.calculPuBernstein(i/resolution, j/resolution);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);

                pUtmp = sr.calculPuBernstein(i/resolution, (j+1)/resolution);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);

                pUtmp = sr.calculPuBernstein((i+1)/resolution, j/resolution);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);
            }

            if(i!=0 && j!=0){
                pUtmp = sr.calculPuBernstein((i-1)/resolution, j/resolution);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);

                pUtmp = sr.calculPuBernstein(i/resolution, j/resolution);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);

                pUtmp = sr.calculPuBernstein(i/resolution, (j-1)/resolution);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);
            }
        }
    }
    glEnd();

    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES);

    for(float j=0; j<=resolution; j++){
        for(float i=0; i<=resolution; i++){
            pUor = sr.calculPuBernstein(i/resolution, j/resolution);
            if(i!=resolution){
                pUtmp = sr.calculPuBernstein((i+1)/resolution, j/resolution);
                glVertex3f(pUor.x, pUor.y, pUor.z);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);
            }


            if(j!=resolution){
                pUtmp = sr.calculPuBernstein(i/resolution, (j+1)/resolution);
                glVertex3f(pUor.x, pUor.y, pUor.z);
                glVertex3f(pUtmp.x, pUtmp.y, pUtmp.z);
            }

        }
    }

    glEnd();

    glFlush();
}
