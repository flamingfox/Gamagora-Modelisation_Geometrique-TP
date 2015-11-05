#pragma once

#include <vector>
#include <float.h>
#include "mesh.h"

class Aretes
{
	std::vector<std::pair<unsigned int, unsigned int>> listArete;
	unsigned int nbVertex;

public:
	Aretes(){};
	Aretes(const Mesh& mesh);

	void recuperationArete(const Mesh& mesh);
	void addArete(const unsigned int &indicePoint1, const unsigned int &indicePoint2);

	inline unsigned int getNbAretes(){ return listArete.size(); };
	inline const std::pair<unsigned int, unsigned int> getArete(unsigned int indiceArete){ return listArete[indiceArete]; };

	void getNbAretesBySommet(float& nbMin, float& nbMax);
	unsigned int getNbAretesBy0Et1Face(const Mesh& mesh);

protected:
	bool Aretes::findPairInVector(const unsigned int &indicePoint1, const unsigned int &indicePoint2) const;
};

