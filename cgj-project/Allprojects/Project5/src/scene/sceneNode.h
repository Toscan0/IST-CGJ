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
		matrix4x4 _modelMatrix;
		//vector3 _color;
		shader* _shader;
		std::vector<sceneNode*> _nodes;
	public:
		sceneNode();
		void setModelMatrix(matrix4x4 &modelMatrix);
		const matrix4x4 getModelMatrix();
		void setMesh(mesh* m);
		const mesh* getMesh();
		void setShader(shader* s);
		const shader* getShader();
		void draw(matrix4x4& modelMatrix);
		void addNode(sceneNode *node);
};