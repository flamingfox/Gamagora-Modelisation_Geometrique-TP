#include "Aretes.h"


Aretes::Aretes(const Mesh& mesh)
{
	recuperationArete(mesh);
}

void Aretes::recuperationArete(const Mesh& mesh){
	std::vector<std::pair<unsigned int, unsigned int>> aretes;

	std::vector<int> face = mesh.getface();

	for(int i=0; i<face.size(); i+=3){
		addArete(face[i], face[i+1]);
		addArete(face[i+1], face[i+2]);
		addArete(face[i], face[i+2]);		
	}

	nbVertex = mesh.getvertex().size();
}

void Aretes::addArete(const unsigned int &indicePoint1, const unsigned int &indicePoint2){	
	if( !findPairInVector(indicePoint1, indicePoint2) ){
		listArete.push_back(std::pair<unsigned int, unsigned int>(indicePoint1, indicePoint2));
	}

	nbVertex++;
}

void Aretes::getNbAretesBySommet(float& nbMin, float& nbMax){

	nbMin = FLT_MAX; nbMax = FLT_MIN;

	for(unsigned int i=0; i<nbVertex; i++){
		int nbAppel = 0;

		for(unsigned int j=0; j<listArete.size(); j++){
			if(listArete[j].first == i || listArete[j].second == i)
				nbAppel++;
		}

		if(nbAppel > nbMax)
			nbMax = nbAppel;
		
		if(nbAppel < nbMin)
			nbMin = nbAppel;
	}
}

unsigned int Aretes::getNbAretesBy0Et1Face(const Mesh& mesh){

	unsigned int areteParatge = 0;

	std::vector<int> face = mesh.getface();

	for(unsigned int j=0; j<listArete.size(); j++){

		//listArete[j].first; listArete[j].second;			

		int nbAppel = 0;

		for(unsigned int i=0; i<face.size(); i+=3){

			if(listArete[j].first == face[i] || listArete[j].first == face[i+1] || listArete[j].first == face[i+2])
				if(listArete[j].second == face[i] || listArete[j].second == face[i+1] || listArete[j].second == face[i+2])
					nbAppel++;			
		}

		if(nbAppel <= 1)
				areteParatge++;
	}

	return areteParatge;
}

bool Aretes::findPairInVector(const unsigned int &indicePoint1, const unsigned int &indicePoint2) const{
	for(int i=0; i<listArete.size(); i++){
		if(indicePoint1 == listArete[i].first || indicePoint1 == listArete[i].second)
			if(indicePoint2 == listArete[i].first || indicePoint2 == listArete[i].second)
				return true;
	}
	return false;
}

