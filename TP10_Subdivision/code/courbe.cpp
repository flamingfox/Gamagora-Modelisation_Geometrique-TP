#include "courbe.h"

void Courbe::addPoint(const point3 &point)
{
    tabPoint.push_back(point);
}

point3& Courbe::operator[] (unsigned int i) {
    if(i < 0 || i >= tabPoint.size()){
        point3 p(0,0,0);
        return p;
    }

    return tabPoint[i];
}

point3 Courbe::operator[] (unsigned int i) const {
    if(i < 0 || i >= tabPoint.size())
        return point3();

    return tabPoint.at(i);
}

Courbe Courbe::subdivision(Courbe courbe, unsigned int depth)
{
    return Chaikin(courbe.tabPoint, depth);
}

Courbe Courbe::Chaikin(std::vector<point3> &listPoint, unsigned int depth)
{
    std::vector<point3> newPoint;

    for(int i=0; i<listPoint.size(); i++){
        newPoint.push_back( listPoint[i]+ (listPoint[(i+1)%listPoint.size()]-listPoint[i])*(1.0/4.0) );
        newPoint.push_back( listPoint[i]+ (listPoint[(i+1)%listPoint.size()]-listPoint[i])*(3.0/4.0) );
    }

    listPoint = newPoint;

    if(depth <= 1)
        return Courbe(newPoint);
    else
        return Chaikin(listPoint, depth-1);

}
