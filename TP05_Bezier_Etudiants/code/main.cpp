#include "windowBernsteinSimple.h"
#include "windowBernsteinDouble.h"
#include "windowHermite.h"
#include "windowCastlejau.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //WindowHermite w;
    //WindowBernsteinSimple w;
    //WindowBernsteinDouble w;
    WindowCastlejau w;
    w.resolution = 40;
    w.show();

    return a.exec();
}
