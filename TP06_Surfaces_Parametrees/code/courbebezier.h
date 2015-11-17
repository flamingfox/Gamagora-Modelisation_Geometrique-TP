#ifndef COURBEBEZIER_H
#define COURBEBEZIER_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include "lib/struct.h"

class CourbeBezier
{
    std::vector<point3> tabPoint;

public:
    CourbeBezier(){}
    CourbeBezier(const std::vector<point3>& listPoint) : tabPoint(listPoint){}

    void addPoint(const point3& point);

    unsigned int getOrdre();
    unsigned int getDegree();

    point3 calculPu(const float& progressionCourbe);

    point3 &operator[] (unsigned int i);
    point3 operator[] (unsigned int i) const;

private:
    // Fonction Factorielle
    float fact(int n);
    float Bernstein(int i, int n, float t);
};

#endif // COURBEBEZIER_H
