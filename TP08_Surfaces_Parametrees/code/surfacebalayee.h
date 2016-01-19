#ifndef SURFACEBALAYEE_H
#define SURFACEBALAYEE_H

#include "courbebezier.h"

class surfaceBalayee
{
    CourbeBezier courbeForme, courbePorteuse;
public:
    surfaceBalayee(){}

    void addPointForme(const point3& point);
    void addPointPorteuse(const point3& point);

    unsigned int getOrdreForme();
    unsigned int getDegreeForme();

    unsigned int getOrdrePorteuse();
    unsigned int getDegreePorteuse();

    point3 calculPu(const float& progressionCourbeForme, const float& progressionCourbePorteuse);
};

#endif // SURFACEBALAYEE_H
