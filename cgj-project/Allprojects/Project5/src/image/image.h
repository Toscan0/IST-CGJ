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

using std::string;
using std::cout;
using std::endl;

class image {
	private:
		int snapCounter = 0;
	
	public:	
		image();
		static GLuint loadTexture(string filenameString);	/* , GLenum minificationFilter = GL_LINEAR, GLenum magnificationFilter = GL_LINEAR);*/
		void snapShot(int width, int height);
};
