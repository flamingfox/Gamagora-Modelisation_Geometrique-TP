#ifndef COURBEBEZIER_H
#define COURBEBEZIER_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include "lib/struct.h"

class Courbe
{
    std::vector<point3> tabPoint;

public:
    Courbe(){}
    Courbe(const std::vector<point3>& listPoint) : tabPoint(listPoint){}

    void addPoint(const point3& point);

    inline int getNbPoint() const { return tabPoint.size();}

    point3 &operator[] (unsigned int i);
    point3 operator[] (unsigned int i) const;

    // Algorithme de Chaikin
    static Courbe subdivision(Courbe courbe, unsigned int depth);

private:
    static Courbe Chaikin(std::vector<point3> &listPoint, unsigned int depth);

};

#endif // COURBEBEZIER_H
