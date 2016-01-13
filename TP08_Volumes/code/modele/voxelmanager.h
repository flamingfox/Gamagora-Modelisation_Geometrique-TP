#ifndef VOXELMANAGER_H
#define VOXELMANAGER_H

#include "voxel.h"
#include "../geometrie/sphere.h"
#include <float.h>

namespace VoxelManager
{

    Voxel getEmptyVoxelWithGoodDimension(const Sphere& sphere, const int& nbCubeParDimension);
    Voxel getEmptyVoxelWithGoodDimension(const std::vector<Sphere>& spheres, const int& nbCubeParDimension);
    Voxel getEmptyVoxelWithGoodDimension(const Sphere& sphere, const Vector3D& dimensionCubeUnitaire);
    Voxel getEmptyVoxelWithGoodDimension(const std::vector<Sphere>& spheres, const Vector3D& dimensionCubeUnitaire);

    Voxel VoxelSphere(const Sphere& sphere, const int& nbCubeParDimension);
    Voxel VoxelSpheres(const std::vector<Sphere>& spheres, const int& nbCubeParDimension);
    Voxel VoxelSpheresIntersection(const std::vector<Sphere>& spheres, const int& nbCubeParDimension);

    Voxel VoxelSphere(const Sphere& sphere, const Vector3D& dimensionCubeUnitaire);
    Voxel VoxelSpheres(const std::vector<Sphere>& spheres, const Vector3D& dimensionCubeUnitaire);
    Voxel VoxelSpheresIntersection(const std::vector<Sphere>& spheres, const Vector3D& dimensionCubeUnitaire);


}

#endif // VOXELMANAGER_H
