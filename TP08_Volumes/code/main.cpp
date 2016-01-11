#include <iostream>
#include "geometrie/vector3d.h"
#include "geometrie/sphere.h"
#include "modele/voxel.h"
#include "modele/voxelmanager.h"
#include "import_export/objmanager.h"
using namespace std;

int main()
{
#define sequence 1

#if(sequence == 0)
    Sphere sph = Sphere(Vector3D(0,0,0), 1);
    Voxel vox = VoxelManager::VoxelSphere(sph, 10);
    ObjManager::voxelSave("test.obj", vox);
#elif(sequence == 1)
    vector<Sphere> list;
    list.push_back(Sphere(Vector3D(0,0,0), 1));
    list.push_back(Sphere(Vector3D(2,0,0), 1));
    Voxel vox = VoxelManager::VoxelSpheres(list, 20);
    ObjManager::voxelSave("test2.obj", vox);
#endif

    return 0;
}

