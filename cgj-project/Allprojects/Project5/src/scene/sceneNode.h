#pragma once
#include <map>
#include <vector>
#include <string>
#include "../matrix/matrixFactory/matrixFactory.h"
#include "../matrix/matrix4x4/matrix4x4.h"
#include "../mesh/mesh.h"
#include "../shader/shader.h"
#include "../qtrn/qtrn.h"
#include "../../src/matrix/matrixFactory/matrixFactory.h"

class sceneNode {
	protected:
		vector3 _translationVector = vector3(0, 0, 0);
		vector3 _scalingVector = vector3(1, 1, 1);
		matrix4x4 _initialModelMatrix;
		matrix4x4 _modelMatrix;
		shader* _shader;
		mesh* _mesh;
		std::string _name;
		float _color[4];
		int _index = -1;
		qtrn _q = { 1.0f, 0.0f, 0.0f, 0.0f }; //quarterion resposible for piece rotation
		std::vector<sceneNode*> _nodes;
		bool _texturesLoaded = false;
		GLint _diffuseTexture, _normalTexture;
	
	public:
		sceneNode();
		
		const matrix4x4 getInitialModelMatrix();
		void setInitialModelMatrix(const matrix4x4& modelMatrix);
		void makeInitialModelMatrix(); //creates a model matrix with scalling/translation and rotation of the node

		void setModelMatrix(const matrix4x4& modelMatrix);
		const matrix4x4 getModelMatrix();
		
		const vector3 getTranslationVector();
		void setTranslationVector(const vector3&);

		const vector3 getScalingVector();
		void setScalingVector(const vector3&);

		void setMesh(mesh* m);
		const mesh* getMesh();

		void setShader(shader* s);
		const shader* getShader();
		
		void setName(std::string name);
		const std::string getName();

		float* getColor();
		void setColor(float* color);
		
		void setIndex(int index);
		const int getIndex();

		const qtrn getRotQtrn();
		void setRotQtrn(const qtrn&);

		void setTextures(GLint diffTex, GLint normTex);

		void addNode(sceneNode *node);
		const std::vector<sceneNode*> getNodes();
	
		void draw(camera& cam, GLuint indexSelected);
		void drawPicked(camera& cam, GLuint indexSelected);
		void drawAux(camera&, matrix4x4&,float*);
};