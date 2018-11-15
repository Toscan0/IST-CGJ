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
		mesh* _mesh;
		matrix4x4 _modelMatrixAux;
		matrix4x4 _modelMatrix;
		//vector3 _color;
		shader* _shader;
		std::string _name;
		std::vector<sceneNode*> _nodes;
	
	public:
		sceneNode();
		
		void setModelMatrixAux(const matrix4x4 &modelMatrixAux);
		const matrix4x4 getModelMatrixAux();

		void setModelMatrix(const matrix4x4 &modelMatrix);
		const matrix4x4 getModelMatrix();
		
		void setMesh(mesh* m);
		const mesh* getMesh();

		void setShader(shader* s);
		const shader* getShader();
		
		void setName(std::string name);
		const std::string getName();
		
		
		void addNode(sceneNode *node);
		const std::vector<sceneNode*> getNodes();
	
		void draw(camera& cam);
};