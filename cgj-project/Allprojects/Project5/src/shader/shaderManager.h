#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "shader.h"

class shaderManager {
protected:
	std::map <std::string, shader*> _shaders;

public:
	shaderManager();

	void insertShader(std::string, shader*);
	shader* getShaderByName(std::string name);
};