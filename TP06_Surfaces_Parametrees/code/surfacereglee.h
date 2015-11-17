#ifndef COURBEREGLEE_H
#define COURBEREGLEE_H

#include "courbebezier.h"

class SurfaceReglee
{
    CourbeBezier courbeForme, courbePorteuse;
public:    
    SurfaceReglee(){}

    void addPointForme(const point3& point);
    void addPointPorteuse(const point3& point);

    unsigned int getOrdreForme();
    unsigned int getDegreeForme();

    unsigned int getOrdrePorteuse();
    unsigned int getDegreePorteuse();

    point3 calculPu(const float& progressionCourbeForme, const float& progressionCourbePorteuse);
};

#endif // COURBEREGLEE_H
