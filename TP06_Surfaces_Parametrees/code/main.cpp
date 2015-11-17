#include "windowSurfaceReglee.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    windowSurfaceReglee w;
    w.resolutionForme = 40;
    w.resolutionPorteuse = 5;
    w.show();

    return a.exec();
}
