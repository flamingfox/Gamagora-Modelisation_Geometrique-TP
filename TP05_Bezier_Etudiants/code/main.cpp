#include "windowBernsteinSimple.h"
#include "windowBernsteinDouble.h"
#include "windowHermite.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //WindowHermite w;
    //WindowBernsteinSimple w;
    WindowBernsteinDouble w;
    //w.resolution = 10;
    w.show();

    return a.exec();
}
