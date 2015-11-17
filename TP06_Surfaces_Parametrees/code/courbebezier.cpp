#include "courbebezier.h"

void CourbeBezier::addPoint(const point3 &point)
{
    tabPoint.push_back(point);
}

unsigned int CourbeBezier::getOrdre()
{
    if(tabPoint.size() > 0)
        return tabPoint.size();
    return 0;
}

unsigned int CourbeBezier::getDegree()
{
    if(tabPoint.size() > 0)
        return tabPoint.size()-1;
    return 0;
}

point3 CourbeBezier::calculPu(const float &progressionCourbe)
{
    point3 pU;

    for(int j=0; j< tabPoint.size(); j++){
        pU = pU + tabPoint[j]*Bernstein(j, getDegree(), progressionCourbe);
    }

    return pU;
}

point3& CourbeBezier::operator[] (unsigned int i) {
    if(i < 0 || i >= tabPoint.size()){
        point3 p(0,0,0);
        return p;
    }

    return tabPoint[i];
}

point3 CourbeBezier::operator[] (unsigned int i) const {
    if(i < 0 || i >= tabPoint.size())
        return point3();

    return tabPoint.at(i);
}

float CourbeBezier::fact(const int n)
{
    float retour = 1;
    for(int i=n; i>0; i--){
        retour *= i;
    }
    return retour;
}

float CourbeBezier::Bernstein(int i, int n, float t)
{
    return fact(n) / (fact(i)*fact(n-i)) * powf(t, i) * powf(1-t, n-i);
}

