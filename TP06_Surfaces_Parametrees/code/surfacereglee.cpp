#include "surfacereglee.h"

void SurfaceReglee::addPointForme(const point3 &point)
{
    courbeForme.addPoint(point);
}

void SurfaceReglee::addPointPorteuse(const point3 &point)
{
    courbePorteuse.addPoint(point);
}

unsigned int SurfaceReglee::getOrdreForme()
{
    return courbeForme.getOrdre();
}

unsigned int SurfaceReglee::getDegreeForme()
{
    return courbeForme.getDegree();
}

unsigned int SurfaceReglee::getOrdrePorteuse()
{
    return courbePorteuse.getOrdre();
}

unsigned int SurfaceReglee::getDegreePorteuse()
{
    return courbePorteuse.getDegree();
}

point3 SurfaceReglee::calculPu(const float &progressionCourbeForme, const float &progressionCourbePorteuse)
{
    point3 retour;
    retour = courbeForme.calculPu(progressionCourbeForme);
    retour = retour + courbePorteuse.calculPu(progressionCourbePorteuse);

    return retour;
}
