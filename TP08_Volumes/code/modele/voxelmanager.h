#ifndef VOXELMANAGER_H
#define VOXELMANAGER_H

#include "voxel.h"
#include "../geometrie/sphere.h"
#include <float.h>

namespace VoxelManager
{
    Voxel VoxelSphere(const Sphere& sphere, const int& nbCubeParDimension);
    Voxel VoxelSpheres(const std::vector<Sphere>& spheres, const int& nbCubeParDimension);
}

#endif // VOXELMANAGER_H
