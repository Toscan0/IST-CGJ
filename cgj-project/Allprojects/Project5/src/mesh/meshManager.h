#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "mesh.h"

class meshManager {
	protected:
		std::map <std::string, mesh*> _meshs;

	public:
		meshManager();
	
		void insertMesh(std::string, mesh*);
		mesh* getMeshByName(std::string name);
};
