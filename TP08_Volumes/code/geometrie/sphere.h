#ifndef SPHERE_H
#define SPHERE_H

#include "geometrie/vector3d.h"

class Sphere
{
public:
    Sphere();
    Sphere(const Vector3D& centre, float rayon);

    bool inOut(const Vector3D& p) const;
    float distance(const Vector3D &p) const;

    inline Vector3D getNormal(const Vector3D& p) const{return (p-centre).normalized();}

    inline float getRayon() const{return rayon;}
    inline Vector3D getCentre() const{return centre;}

    protected:

    Vector3D centre;
    float rayon;
};

#endif // SPHERE_H
