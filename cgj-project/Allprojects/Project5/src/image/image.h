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
<<<<<<< HEAD
	private:
		int snapCounter = 0;
	
	public:	
		image();
		static GLuint loadTexture(string filenameString);	/* , GLenum minificationFilter = GL_LINEAR, GLenum magnificationFilter = GL_LINEAR);*/
		void snapShot(int width, int height);
=======
	
	public:	
		image();
		static GLuint loadTexture(string filenameString);	// , GLenum minificationFilter = GL_LINEAR, GLenum magnificationFilter = GL_LINEAR);
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
};
