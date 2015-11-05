#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

#include "mesh.h"

class OFFManager
{
public:
	static Mesh meshLoader(const std::string& fichier);
	static void meshWriter(const std::string& fichier, const Mesh& toSave);
};

