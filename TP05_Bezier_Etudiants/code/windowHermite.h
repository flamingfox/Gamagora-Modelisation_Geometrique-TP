#ifndef WINDOWHERMITE_H
#define WINDOWHERMITE_H

#include "lib/myGLWidget.h"
#include <QImage>

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "lib/struct.h"

class WindowHermite : public myGLWidget
{

public:
    unsigned int resolution = 10;

    explicit WindowHermite(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent( QKeyEvent *keyEvent );

private:
    float hermite(const point3& p0, const point3& p1, const point3& v0, const point3& v1);
};

#endif // WINDOWHERMITE_H
