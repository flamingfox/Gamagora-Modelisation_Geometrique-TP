#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include <math.h>
#include "float.h"

#include "struct.h"

#include <algorithm>

#include <GL/glut.h>

class Mesh{

protected:
    std::vector<point3> vertex;
    std::vector<point3> normalsPoints;
    std::vector<int> face;

public :

    Mesh(){}
    Mesh(std::vector<point3> listvertex, std::vector<int> listface): vertex(listvertex), face(listface)  {}

    ~Mesh(){}

    void merge(const Mesh &delta);

    std::vector<point3> getvertex() const;
    std::vector<int> getface() const;
    void setvertex(std::vector<point3> vertex);
    void setface(std::vector<int> face);
    size_t nbvertex() const;
    size_t nbface() const;

	void translation(const float x, const float y, const float z);
	void rescale(float scale);

	void affichage();

protected:

};


#endif // MESH_H
