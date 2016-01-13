#include "voxelmanager.h"

Voxel VoxelManager::getEmptyVoxelWithGoodDimension(const Sphere &sphere, const int &nbCubeParDimension)
{
    std::vector<Sphere> listTmp;
    listTmp.push_back(sphere);

    return getEmptyVoxelWithGoodDimension(listTmp, nbCubeParDimension);
}

Voxel VoxelManager::getEmptyVoxelWithGoodDimension(const std::vector<Sphere> &spheres, const int &nbCubeParDimension)
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

    return Voxel(posMin,posMax, nbCubeParDimension);
}

Voxel VoxelManager::getEmptyVoxelWithGoodDimension(const Sphere &sphere, const Vector3D &dimensionCubeUnitaire)
{

    std::vector<Sphere> listTmp;
    listTmp.push_back(sphere);

    return getEmptyVoxelWithGoodDimension(listTmp, dimensionCubeUnitaire);

}

Voxel VoxelManager::getEmptyVoxelWithGoodDimension(const std::vector<Sphere> &spheres, const Vector3D &dimensionCubeUnitaire)
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

    float distanceDimensionX = posMax.x - posMin.x;

    int nbCubeParDimension = (int) (roundf(distanceDimensionX/dimensionCubeUnitaire.x));

    posMax = posMin + dimensionCubeUnitaire*nbCubeParDimension;

    return Voxel(posMin,posMax, nbCubeParDimension);
}


Voxel VoxelManager::VoxelSphere(const Sphere &sphere, const int &nbCubeParDimension)
{
    Voxel retour = getEmptyVoxelWithGoodDimension(sphere, nbCubeParDimension);

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

    Voxel retour = getEmptyVoxelWithGoodDimension(spheres, nbCubeParDimension);

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

Voxel VoxelManager::VoxelSpheresIntersection(const std::vector<Sphere> &spheres, const int &nbCubeParDimension)
{
    Voxel retour = getEmptyVoxelWithGoodDimension(spheres, nbCubeParDimension);

    Vector3D dimCubeUnitaire = retour.getDimensionCubeUnitaire();

    int intersection = 0;

    for(int i=0; i<nbCubeParDimension; i++){
        for(int j=0; j<nbCubeParDimension; j++){
            for(int k=0; k<nbCubeParDimension; k++){

                intersection = 0;

                Vector3D tmp = retour.getPosMin();
                tmp.x += (i+0.5)*dimCubeUnitaire.x;
                tmp.y += (j+0.5)*dimCubeUnitaire.y;
                tmp.z += (k+0.5)*dimCubeUnitaire.z;

                for(Sphere sphere : spheres){
                    if(sphere.inOut(tmp)){
                        intersection++;
                    }
                }

                if(intersection>1){
                    retour(i,j,k) = 1;
                }

            }
        }
    }

    return retour;
}

Voxel VoxelManager::VoxelSphere(const Sphere &sphere, const Vector3D &dimensionCubeUnitaire)
{
    Voxel retour = getEmptyVoxelWithGoodDimension(sphere, dimensionCubeUnitaire);

    int nbCubeParDimension = retour.getNbCubeParDimension();

    for(int i=0; i<nbCubeParDimension; i++){
        for(int j=0; j<nbCubeParDimension; j++){
            for(int k=0; k<nbCubeParDimension; k++){

                Vector3D tmp = retour.getPosMin();
                tmp.x += (i+0.5)*dimensionCubeUnitaire.x;
                tmp.y += (j+0.5)*dimensionCubeUnitaire.y;
                tmp.z += (k+0.5)*dimensionCubeUnitaire.z;

                if(sphere.inOut(tmp))
                    retour(i,j,k) = 1;
            }
        }
    }

    return retour;
}

Voxel VoxelManager::VoxelSpheres(const std::vector<Sphere> &spheres, const Vector3D &dimensionCubeUnitaire)
{
    Voxel retour = getEmptyVoxelWithGoodDimension(spheres, dimensionCubeUnitaire);

    int nbCubeParDimension = retour.getNbCubeParDimension();

    for(int i=0; i<nbCubeParDimension; i++){
        for(int j=0; j<nbCubeParDimension; j++){
            for(int k=0; k<nbCubeParDimension; k++){

                Vector3D tmp = retour.getPosMin();
                tmp.x += (i+0.5)*dimensionCubeUnitaire.x;
                tmp.y += (j+0.5)*dimensionCubeUnitaire.y;
                tmp.z += (k+0.5)*dimensionCubeUnitaire.z;

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

Voxel VoxelManager::VoxelSpheresIntersection(const std::vector<Sphere> &spheres, const Vector3D &dimensionCubeUnitaire)
{
    Voxel retour = getEmptyVoxelWithGoodDimension(spheres, dimensionCubeUnitaire);

    int nbCubeParDimension = retour.getNbCubeParDimension();

    int intersection = 0;

    for(int i=0; i<nbCubeParDimension; i++){
        for(int j=0; j<nbCubeParDimension; j++){
            for(int k=0; k<nbCubeParDimension; k++){

                intersection = 0;

                Vector3D tmp = retour.getPosMin();
                tmp.x += (i+0.5)*dimensionCubeUnitaire.x;
                tmp.y += (j+0.5)*dimensionCubeUnitaire.y;
                tmp.z += (k+0.5)*dimensionCubeUnitaire.z;

                for(Sphere sphere : spheres){
                    if(sphere.inOut(tmp)){
                        intersection++;
                    }
                }

                if(intersection>1){
                    retour(i,j,k) = 1;
                }

            }
        }
    }

    return retour;
}
