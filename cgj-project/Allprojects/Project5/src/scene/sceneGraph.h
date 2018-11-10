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
	shader* _shader;
	sceneNode* _root;
	GLuint uboHandle;
	GLuint UboID;
	GLubyte *blockBuffer;
	GLint blockSize;
	GLuint indices[7];
	GLint offset[7];
	GLchar *names[7];

	sceneGraph(camera* camera, shader* shader);

	void InitializeUniformBlock();

	void setCamera(camera *c);
	camera* getCamera();

	void setShader(shader *s);
	shader* getShader();

	void setRoot(sceneNode *r);
	sceneNode *getRoot();

	void draw();
};