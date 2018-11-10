#include "sceneGraph.h"

sceneGraph::sceneGraph(camera* camera, shader* shader) {
	_camera = camera;
	_shader = shader;
}

//void sceneGraph::InitializeUniformBlock();

void sceneGraph::setCamera(camera* c) {
	_camera = c;
}

camera* sceneGraph::getCamera() {
	return _camera;
}

void sceneGraph::setShader(shader* s) {
	_shader = s;
}
shader* sceneGraph::getShader() {
	return _shader;
}

void sceneGraph::setRoot(sceneNode *r) {
	_root = r;
}

sceneNode* sceneGraph::getRoot() {
	return _root;
}