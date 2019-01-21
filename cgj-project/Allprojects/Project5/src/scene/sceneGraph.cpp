#include "sceneGraph.h"

sceneGraph::sceneGraph() {}

sceneGraph::sceneGraph(camera* camera) {
	this->setCamera(camera);
}

void sceneGraph::setCamera(camera* c) {
	_camera = c;
}

camera* sceneGraph::getCamera() {
	return _camera;
}

void sceneGraph::setRoot(sceneNode *r) {
	_root = r;
}

sceneNode* sceneGraph::getRoot() {
	return _root;
}

const GLuint sceneGraph::getIndex() {
	return _index;
}

void sceneGraph::setIndex(GLuint index) {
	_index = index;
}

sceneNode* sceneGraph::getNodeSelected() {
	return _nodeSelected;
}

void sceneGraph::setNodeSelected(sceneNode* nodeSelected) {
	_nodeSelected = nodeSelected;
}

void sceneGraph::draw() {
	_root->draw(*_camera, _index);
	_root->drawPicked(*_camera, _index);
}