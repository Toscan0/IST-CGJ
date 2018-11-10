#include "sceneNode.h"

sceneNode::sceneNode() {}

void sceneNode::setModelMatrix(matrix4x4 &modelMatrix) {
	_modelMatrix = modelMatrix;
}

const matrix4x4 sceneNode::getModelMatrix() {
	return _modelMatrix;
}

void sceneNode::setMesh(mesh* m) {
	_mesh = m;
}

const mesh* sceneNode::getMesh() {
	return _mesh;
}

void sceneNode::setShader(shader* s) {
	_shader = s;
}

const shader* sceneNode::getShader() {
	return _shader;
}

void sceneNode::addNode(sceneNode* node) {
	_nodes.push_back(node);
}