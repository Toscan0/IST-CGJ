#pragma once
#include <map>
#include <vector>
#include <string>
#include "../matrix/matrixFactory/matrixFactory.h"
#include "../matrix/matrix4x4/matrix4x4.h"
#include "../mesh/mesh.h"
#include "../shader/shader.h"
#include "../camera/camera.h"
#include "sceneNode.h"

class sceneGraph {
public:
	camera* _camera;
	sceneNode* _root;
	// piece selected
	GLuint _index; //index of the piece selected
	sceneNode *_nodeSelected = nullptr; // node of the piece

	sceneGraph();
	sceneGraph(camera* camera);

	void setCamera(camera *c);
	camera* getCamera();

	void setRoot(sceneNode *r);
	sceneNode *getRoot();

	const GLuint getIndex();
	void setIndex(GLuint index);

	sceneNode* getNodeSelected();
	void setNodeSelected(sceneNode*);
	
	void draw();
};