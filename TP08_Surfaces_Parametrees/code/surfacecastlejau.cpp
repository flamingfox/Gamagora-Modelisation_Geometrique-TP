#include "surfacecastlejau.h"

void SurfaceCastlejau::addPointForme(const point3 &point)
{
    courbeForme.addPoint(point);
}

void SurfaceCastlejau::addPointPorteuse(const point3 &point)
{
    courbePorteuse.addPoint(point);
}

unsigned int SurfaceCastlejau::getOrdreForme()
{
    return courbeForme.getOrdre();
}

unsigned int SurfaceCastlejau::getDegreeForme()
{
    return courbeForme.getDegree();
}

unsigned int SurfaceCastlejau::getOrdrePorteuse()
{
    return courbePorteuse.getOrdre();
}

unsigned int SurfaceCastlejau::getDegreePorteuse()
{
    return courbePorteuse.getDegree();
}

point3 SurfaceCastlejau::calculPuCastlejau(const float &progressionCourbeForme, const float &progressionCourbePorteuse)
{
    point3 retour;
    retour = courbeForme.calculPuCastlejau(progressionCourbeForme);
    retour = retour + courbePorteuse.calculPuCastlejau(progressionCourbePorteuse);

    return retour;
}
