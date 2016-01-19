#include <QApplication>

#include "windowSurfaceCastlejau.h"
#include "windowSurfaceReglee.h"
#include "windowSurfaceBalayee.h"

#define sequence 1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



//#if(sequence==0)
    windowSurfaceCastlejau wc;
    wc.resolution = 20;
    wc.show();
//#elif(sequence==1)
    windowSurfaceReglee wr;
    wr.resolution = 20;
    wr.show();
//#elif(sequence==2)
    windowSurfaceBalayee wb;
    wb.resolutionForme = 20;
    wb.resolutionPorteuse = 20;
    wb.show();
//#endif

    return a.exec();
}
