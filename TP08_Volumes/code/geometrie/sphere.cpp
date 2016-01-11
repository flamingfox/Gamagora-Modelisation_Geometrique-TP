#include "sphere.h"

Sphere::Sphere():
    Sphere(Vector3D(0.f,0.f,0.f), 0)
{
}

Sphere::Sphere(const Vector3D &centre, float rayon):
    centre(centre), rayon(rayon)
{

}

bool Sphere::inOut(const Vector3D& p) const
{
    return distance2(centre, p) <= rayon*rayon;
}

float Sphere::distance(const Vector3D& p) const
{
    float dst2 = distance2(centre, p);

    if(dst2 > rayon*rayon)
        return sqrt(dst2)-rayon;
    else
        return 0;
}
