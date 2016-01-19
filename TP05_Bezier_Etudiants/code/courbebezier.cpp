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

point3 CourbeBezier::calculPuBernstein(const float &progressionCourbe)
{
    point3 pU;

    for(int j=0; j< tabPoint.size(); j++){
        pU = pU + tabPoint[j]*Bernstein(j, getDegree(), progressionCourbe);
    }

    return pU;
}

point3 CourbeBezier::calculPuCastlejau(const float &progressionCourbe)
{
    return castlejau(tabPoint, progressionCourbe);
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

point3 CourbeBezier::castlejau(std::vector<point3>& pointI, float u)
{
    if(pointI.size() == 2 ){
        return pointI[0]+(pointI[1]-pointI[0])*u;
    }

    std::vector<point3> pointTmp;

    for(int i=0; i<pointI.size()-1; i++){
        pointTmp.push_back(pointI[i]+(pointI[i+1]-pointI[i])*u);
    }

    return castlejau(pointTmp, u);
}

