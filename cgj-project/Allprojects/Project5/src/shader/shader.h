#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
#include "GL/glew.h"
#include "../error/error.h"

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2
#define COLORS 3
<<<<<<< HEAD

class shader {
	protected:
		GLuint _ProgramId;
=======
class shader {
	protected:
		//bool _TexcoordsLoaded, _NormalsLoaded;
		GLuint _ProgramId, _colorId;
		//GLint _ModelMatrix_UId, _ViewMatrix_UId, _ProjectionMatrix_UId;
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
		std::vector<GLuint> _shaders;
		std::map <const GLchar*, GLint> _uniforms;

	public:	
		shader();
		
		const std::string read(const std::string& filename);
		const GLuint checkCompilation(const GLuint shader_id, const std::string& filename);
		void checkLinkage(const GLuint program_id);
<<<<<<< HEAD
		void addShader(const GLenum shader_type, const std::string& filename);
=======
		/*const GLuint addShader(const GLuint program_id, 
			const GLenum shader_type, const std::string& filename);*/
		void addShader(const GLenum shader_type, const std::string& filename);
		GLint getUniform(const GLchar* name);
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
		void createShaderProgram(const std::string& vs_file, const std::string& fs_file, bool texcoordsLoaded, bool mormalsLoaded);
		void destroyShaderProgram();

		void Bind() const;
		void UnBind() const;
<<<<<<< HEAD
=======

		// get & set
		//const bool getTexcoordsLoaded(); 
		//const bool getNormalsLoaded();
		//const void setTexcoordsLoaded(const bool texCoordsLoaded);
		//const void setNormalsLoaded(const bool normalsLoaded);
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7

		// get & set
		const GLuint getProgramId();
<<<<<<< HEAD
		GLint getUniform(const GLchar* name);
=======
		//const GLint getModelMatrix_UId();
		//const GLint getViewMatrix_UId();
		//const GLint getProjectionMatrix_UId();

		const GLuint getColorId();
		//void setColorId(const GLuint);
>>>>>>> 02ddc96a5953f7d188d6cb2c68c02ee8092c5ae7
};
