#include "windowSurfaceReglee.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    windowSurfaceReglee w;
    w.resolution = 40;
    w.show();

    return a.exec();
}
