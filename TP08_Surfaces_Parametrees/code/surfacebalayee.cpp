#include "surfacebalayee.h"

void surfaceBalayee::addPointForme(const point3 &point)
{
    courbeForme.addPoint(point);
}

void surfaceBalayee::addPointPorteuse(const point3 &point)
{
    courbePorteuse.addPoint(point);
}

unsigned int surfaceBalayee::getOrdreForme()
{
    return courbeForme.getOrdre();
}

unsigned int surfaceBalayee::getDegreeForme()
{
    return courbeForme.getDegree();
}

unsigned int surfaceBalayee::getOrdrePorteuse()
{
    return courbePorteuse.getOrdre();
}

unsigned int surfaceBalayee::getDegreePorteuse()
{
    return courbePorteuse.getDegree();
}

point3 surfaceBalayee::calculPu(const float &progressionCourbeForme, const float &progressionCourbePorteuse)
{
    point3 retour;
    retour = courbeForme.calculPuBernstein(progressionCourbeForme);
    retour = retour + courbePorteuse.calculPuCastlejau(progressionCourbePorteuse);

    return retour;
}
