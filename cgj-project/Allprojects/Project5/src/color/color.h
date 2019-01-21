#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "GL/glew.h"
#include "../error/error.h"
#include "FreeImage.h"
#include <map>

class color {
	protected:
		//Colors
		
		float _red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
		float _green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
		float _blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
		float _blue2[4] = { 0.03f, 0.01f, 0.7f, 1.0f };
		float _black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float _white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float _yellow[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
		float _orange[4] = { 1.0f, 0.5f, 0.1f, 1.0f };
		float _purple[4] = { 0.8f, 0.0f, 0.2f, 1.0f };
		float _pink[4] = { 1.0f, 0.5f, 0.5f, 1.0f };
		float _brown[4] = { 0.164f, 0.074f, 0.015f, 1.0f };
		float _brown2[4] = { 0.1f, 0.0f, 0.2f, 1.0f };
		
		std::map <std::string , float*> _colors;
	
	public:
		color();
		float* getColorByName(std::string name);
};

