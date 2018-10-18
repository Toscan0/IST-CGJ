#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <fstream>
#include "GL/glew.h"
//#include "../shapes.h"

#define VERTICES 0
#define COLORS 1

class shaders {
	GLuint _VertexShaderId, _FragmentShaderId, _ProgramId;
	GLint _UniformId, _colorShader;
	
	public:	
		std::string readShaderFile(const char *shader_file);
		
		void createShader();
		void destroyShader();
		void createBuffer();
		void destroyBuffer();

		// get 
		/*
		GLuint getVaoIdSTri();
		GLuint getVboIdSTri();
		GLuint getVaoIdSquare();
		GLuint getVboIdSquare();
		GLuint getVaoIdParall();
		GLuint getVboIdParall();*/
		GLuint getVertexShaderId();
		GLuint getFragmentShaderId();
		GLuint getProgramId();
		GLint  getUniformId();
		GLint  getcolorShader();
};
