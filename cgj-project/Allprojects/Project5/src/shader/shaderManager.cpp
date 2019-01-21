#include "shaderManager.h"

shaderManager::shaderManager() {}

void shaderManager::insertShader(std::string name, shader* m) {
	_shaders.insert(std::pair<std::string, shader*>(std::string(name), m));
}

shader* shaderManager::getShaderByName(std::string name) {
	std::map <std::string, shader*> ::iterator it = _shaders.find(name);
	if (it == _shaders.end()) { /* Not found */ }
	else {
		/* Found, i->first is f, i->second is ++-- */
		return it->second;
	}
}
