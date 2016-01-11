#include "voxel.h"

Voxel::Voxel():_nbCubeParDimension(0), _posMin(0,0,0), _posMax(1,1,1){
}

Voxel::Voxel(const Vector3D &posMin, const Vector3D &posMax, const int &nbCubeParDimension):_nbCubeParDimension(nbCubeParDimension), _posMin(posMin), _posMax(posMax){
    v.resize(nbCubeParDimension*nbCubeParDimension*nbCubeParDimension);
}
