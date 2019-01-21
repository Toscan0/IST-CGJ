#include "meshManager.h"

meshManager::meshManager() {}

void meshManager::insertMesh(std::string name, mesh* m) {
	_meshs.insert(std::pair<std::string, mesh*>(std::string(name), m));
}

mesh* meshManager::getMeshByName(std::string name){
	std::map <std::string, mesh*> ::iterator it = _meshs.find(name);
	if (it == _meshs.end()) { /* Not found */ }
	else {
		/* Found, i->first is f, i->second is ++-- */
		return it->second;
	}
}

