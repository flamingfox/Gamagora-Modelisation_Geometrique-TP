#ifndef SURFACECASTLEJAU_H
#define SURFACECASTLEJAU_H

#include "courbebezier.h"

class SurfaceCastlejau
{
    CourbeBezier courbeForme, courbePorteuse;
public:
    SurfaceCastlejau(){}

    void addPointForme(const point3& point);
    void addPointPorteuse(const point3& point);

    unsigned int getOrdreForme();
    unsigned int getDegreeForme();

    unsigned int getOrdrePorteuse();
    unsigned int getDegreePorteuse();

    point3 calculPuCastlejau(const float& progressionCourbeForme, const float& progressionCourbePorteuse);
};

#endif // COURBEREGLEE_H
