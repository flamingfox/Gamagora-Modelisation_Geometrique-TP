#ifndef VOXEL_H
#define VOXEL_H
#include "vector"
#include "string"
#include "geometrie/vector3d.h"

class Voxel
{
public:
    Voxel();
    Voxel(const Vector3D& posMin, const Vector3D& posMax, const int& nbCubeParDimension);

    int operator()(int i, int j, int k)const{return v.at(i*_nbCubeParDimension*_nbCubeParDimension+j*_nbCubeParDimension+k);}
    int& operator()(int i, int j, int k){return v[i*_nbCubeParDimension*_nbCubeParDimension+j*_nbCubeParDimension+k];}
    inline int getNbCubeParDimension()const{return _nbCubeParDimension;}
    inline Vector3D getPosMin()const{return _posMin;}
    inline void setPosMin(const Vector3D& posMin){_posMin=posMin;}
    inline Vector3D getPosMax()const{return _posMax;}
    inline void setPosMax(const Vector3D& posMax){_posMax=posMax;}

    inline Vector3D getDimensionCubeUnitaire() const{return (_posMax - _posMin)/_nbCubeParDimension ;}

private:
    Vector3D _posMin, _posMax;
    std::vector<int>v;
    int _nbCubeParDimension;
};

#endif // VOXEL_H
