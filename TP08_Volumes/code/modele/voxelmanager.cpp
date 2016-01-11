#include "voxelmanager.h"

Voxel VoxelManager::VoxelSphere(const Sphere &sphere, const int &nbCubeParDimension)
{
    Voxel retour = Voxel(sphere.getCentre() - sphere.getRayon(),
                        sphere.getCentre() + sphere.getRayon(),
                        nbCubeParDimension);

    Vector3D dimCubeUnitaire = retour.getDimensionCubeUnitaire();

    for(int i=0; i<nbCubeParDimension; i++){
        for(int j=0; j<nbCubeParDimension; j++){
            for(int k=0; k<nbCubeParDimension; k++){

                Vector3D tmp = retour.getPosMin();
                tmp.x += (i+0.5)*dimCubeUnitaire.x;
                tmp.y += (j+0.5)*dimCubeUnitaire.y;
                tmp.z += (k+0.5)*dimCubeUnitaire.z;

                if(sphere.inOut(tmp))
                    retour(i,j,k) = 1;
            }
        }
    }

    return retour;
}

Voxel VoxelManager::VoxelSpheres(const std::vector<Sphere> &spheres, const int &nbCubeParDimension)
{
    Vector3D posMin( FLT_MAX, FLT_MAX, FLT_MAX ), posMax (FLT_MIN, FLT_MIN, FLT_MIN);

    for(Sphere sphere : spheres){

        Vector3D posMinTmp = sphere.getCentre()-sphere.getRayon(),
                posMaxTmp = sphere.getCentre()+sphere.getRayon();

        if(posMinTmp.x < posMin.x || posMinTmp.y < posMin.y || posMinTmp.z < posMin.z)
            posMin = sphere.getCentre()-sphere.getRayon();

        if(posMaxTmp.x > posMax.x || posMaxTmp.y > posMax.y || posMaxTmp.z > posMax.z)
            posMax = sphere.getCentre()+sphere.getRayon();

    }

    /*

      Pour avoir un espace voxel cubique

    */
    float minHomogene = posMin.x;
    if(minHomogene > posMin.y)
        minHomogene = posMin.y;
    if(minHomogene > posMin.z)
        minHomogene = posMin.z;

    posMin = Vector3D(minHomogene, minHomogene, minHomogene);

    float maxHomogene = posMax.x;
    if(maxHomogene < posMax.y)
        maxHomogene = posMax.y;
    if(maxHomogene < posMax.z)
        maxHomogene = posMax.z;

    posMax = Vector3D(maxHomogene, maxHomogene, maxHomogene);

    /*
     *
     * */

    Voxel retour = Voxel(posMin,posMax, nbCubeParDimension);

    Vector3D dimCubeUnitaire = retour.getDimensionCubeUnitaire();

    for(int i=0; i<nbCubeParDimension; i++){
        for(int j=0; j<nbCubeParDimension; j++){
            for(int k=0; k<nbCubeParDimension; k++){

                Vector3D tmp = retour.getPosMin();
                tmp.x += (i+0.5)*dimCubeUnitaire.x;
                tmp.y += (j+0.5)*dimCubeUnitaire.y;
                tmp.z += (k+0.5)*dimCubeUnitaire.z;

                for(Sphere sphere : spheres){
                    if(sphere.inOut(tmp)){
                        retour(i,j,k) = 1;
                        break;
                    }
                }
            }
        }
    }

    return retour;

}
