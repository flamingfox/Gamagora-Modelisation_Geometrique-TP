#include "windowSubdivision.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowSubdivision w;
    w.show();

    return a.exec();
}
