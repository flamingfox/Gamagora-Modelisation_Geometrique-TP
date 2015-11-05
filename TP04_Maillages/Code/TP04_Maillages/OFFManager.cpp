#include "OFFManager.h"


Mesh OFFManager::meshLoader(const std::string& fichier){
	std::ifstream off;

    off.open(fichier.c_str(), std::ios::out);

	if(!off.good())
		exit(-1);

	std::string line;

	std::getline(off, line);

	float nbvertex, nbface, nbArret;

	off >> nbvertex >> nbface >> nbArret;

	std::vector<point3> vertex;	vertex.resize(nbvertex);
	std::vector<int> face;	face.resize(nbface*3);

	point3 sommet, centreGravite(0,0,0);

    for(int i = 0 ; i < nbvertex; i++) {
        off >> sommet.x >> sommet.y >> sommet.z;
		vertex[i] = sommet;
		centreGravite = centreGravite + sommet;
    }

	centreGravite = centreGravite / nbvertex;

	int tmp, ref1, ref2, ref3;
    for(int i = 0 ; i < nbface*3; i += 3){
		
		off >> tmp >> face[i] >> face[i+1] >> face[i+2];
    }

    off.close();

    std::cout << "load " << fichier << std::endl;

	/**
		Nettoyage :
		centrage + normalisation
	**/
	float normalizeScale = 0;
	for(point3& p: vertex){
		if(fabs(p.x) > normalizeScale)
			normalizeScale = fabs(p.x);

		if(fabs(p.y) > normalizeScale)
			normalizeScale = fabs(p.y);

		if(fabs(p.z) > normalizeScale)
			normalizeScale = fabs(p.z);
	}

	Mesh retour = Mesh(vertex, face);
	retour.translation(-centreGravite.x, -centreGravite.y, -centreGravite.z);
	retour.rescale(1.0/normalizeScale);

	return retour;
}

void OFFManager::meshWriter(const std::string& fichier, const Mesh& toSave){

    std::ofstream off;

    off.open(fichier.c_str(), std::ios::out);

	off << "OFF\n";
	off << toSave.nbvertex() << " " << toSave.nbface() / 3 << " " << "\n";

	std::vector<point3> vertex = toSave.getvertex();

    for(size_t i = 0 ; i < vertex.size(); i++) {
        off << setprecision(5) << vertex[i].x << " " << vertex[i].y << " " << vertex[i].z << "\n";
    }

	std::vector<int> face = toSave.getface();

    for(size_t i = 0 ; i < face.size(); i += 3){
        off << "3 " << face[i] << " " << face[i+1] << " " << face[i+2] << "\n";
    }

    off << "\n";

    off.close();

    std::cout << "wrote " << fichier << std::endl;
}