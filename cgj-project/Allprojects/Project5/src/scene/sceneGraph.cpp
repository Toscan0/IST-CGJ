#include "sceneGraph.h"

sceneGraph::sceneGraph() {}

sceneGraph::sceneGraph(camera* camera, shader* shader) {
	this->setCamera(camera);
	this->setShader(shader);
}

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

void sceneGraph::draw(matrix4x4& modelMatrix) {
	_root->draw(modelMatrix);
}