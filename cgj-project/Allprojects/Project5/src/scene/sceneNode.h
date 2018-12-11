#pragma once
#include <map>
#include <vector>
#include <string>
#include "../matrix/matrixFactory/matrixFactory.h"
#include "../matrix/matrix4x4/matrix4x4.h"
#include "../mesh/mesh.h"
#include "../shader/shader.h"

class sceneNode {
	protected:
		vector3 _translationVector = vector3(0, 0, 0);
		vector3 _scalingVector = vector3(1, 1, 1);
		vector3 _rotationVector = vector3(0, 0, 0);
		double _angle = 0;
		matrix4x4 _initialModelMatrix;
		matrix4x4 _modelMatrix;
		shader* _shader;
		mesh* _mesh;
		std::string _name;
		int _index = -1;
		qtrn _q = { 1.0f, 0.0f, 0.0f, 0.0f }; //quarterion resposible for piece rotation
		std::vector<sceneNode*> _nodes;
	
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

		const vector3 getRotationVector();
		void setRotationVector(const vector3&);

		const double getAngle();
		void setAngle(const double);

		void setMesh(mesh* m);
		const mesh* getMesh();

		void setShader(shader* s);
		const shader* getShader();
		
		void setName(std::string name);
		const std::string getName();

		void setIndex(int index);
		const int getIndex();

		const qtrn getRotQtrn();
		void setRotQtrn(const qtrn&);

		void addNode(sceneNode *node);
		const std::vector<sceneNode*> getNodes();
	
		void draw(camera& cam);
};