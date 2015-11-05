#include "mesh.h"


/* -------------------------------------------- */
/* -------------------------------------------- */
/* -------------------------------------------- */
/*            Fonctions utilitaires             */
/* -------------------------------------------- */
/* -------------------------------------------- */
/* -------------------------------------------- */

void Mesh::merge(const Mesh &delta)
{
	if(&delta != this){
		int taille = vertex.size();
		vertex.reserve(taille+delta.nbvertex());

		for(size_t i=0; i< delta.vertex.size(); i++){
			vertex.push_back(delta.vertex[i]);
		}

		face.reserve(this->nbface()+delta.nbface());
		for(size_t i=0; i< delta.face.size(); i++){
			face.push_back(delta.face[i] + taille );
		}
	}
}

/* -------------------------------------------- */
/* -------------------------------------------- */
/* -------------------------------------------- */
/*            Fonctions accessors               */
/* -------------------------------------------- */
/* -------------------------------------------- */
/* -------------------------------------------- */

std::vector<point3> Mesh::getvertex() const{
	return vertex;
}

std::vector<int> Mesh::getface() const{
	return face;
}

size_t Mesh::nbvertex() const
{
	return this->vertex.size();
}

size_t Mesh::nbface() const
{
	return this->face.size();
}


void Mesh::translation(const float x, const float y, const float z)
{
	for(point3& p: vertex){
		p.x+=x;
		p.y+=y;
		p.z+=z;
	}
}

void Mesh::rescale(float scale)
{
	for(point3& p: vertex){
		p *= scale;
	}
}


void Mesh::affichage(){	

	for (int i = 0; i < face.size(); i+=3)
	{
		point3 normal = (vertex[face[i+2]]-vertex[face[i]])^(vertex[face[i+1]]-vertex[face[i]]);

		normal.normalize();

		glColor3f(0.8,0.3,0.3);
		glBegin(GL_TRIANGLES);
		glNormal3f(normal.x, normal.y, normal.z);
		glVertex3f(vertex[face[i]].x, vertex[face[i]].y, vertex[face[i]].z);
		glVertex3f(vertex[face[i+1]].x, vertex[face[i+1]].y, vertex[face[i+1]].z);
		glVertex3f(vertex[face[i+2]].x, vertex[face[i+2]].y, vertex[face[i+2]].z);
		glEnd();
	}	
}