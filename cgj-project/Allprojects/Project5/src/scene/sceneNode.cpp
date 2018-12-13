#include "sceneNode.h"

sceneNode::sceneNode() {}

void sceneNode::makeInitialModelMatrix() {
	matrixFactory mf;

	//For transformation the order is : T * R * S
	this->setInitialModelMatrix(
		mf.translationMatrix4x4(_translationVector) *
		mf.rotationMatrix4x4(_rotationVector, _angle) *
		mf.scalingMatrix4x4(_scalingVector)
	);
}

void sceneNode::setInitialModelMatrix(const matrix4x4 &initialModelMatrix) {
	_initialModelMatrix = initialModelMatrix;

	this->setModelMatrix(initialModelMatrix);
}

const matrix4x4 sceneNode::getInitialModelMatrix() {
	return _initialModelMatrix;
}

void sceneNode::setModelMatrix(const matrix4x4 &modelMatrix) {
	_modelMatrix = modelMatrix;
	// if is a parent node you need to updated the model matrix of his sons
	for (int i = 0; i < _nodes.size(); i++) {
		sceneNode* nextNode = _nodes[i];
		nextNode->setModelMatrix(modelMatrix *  nextNode->getInitialModelMatrix());
	}
}

const matrix4x4 sceneNode::getModelMatrix() {
	return _modelMatrix;
}

const vector3 sceneNode::getTranslationVector() {
	return _translationVector;
}

void sceneNode::setTranslationVector(const vector3& vt) {
	_translationVector = vt;
}

const vector3 sceneNode::getScalingVector() {
	return _scalingVector;
}

void sceneNode::setScalingVector(const vector3& vS) {
	_scalingVector = vS;
}

const vector3 sceneNode::getRotationVector() {
	return _rotationVector;
}

void sceneNode::setRotationVector(const vector3& vR) {
	_rotationVector = vR;
}

const double sceneNode::getAngle() {
	return _angle;
}

void sceneNode::setAngle(const double teta) {
	_angle = teta;
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

void sceneNode::setName(std::string name) {
	_name = name;
}

const std::string sceneNode::getName() {
	return _name;
}

float* sceneNode::getColor() {
	return _color;
}

void sceneNode::setColor(float* color) {
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];
	_color[3] = color[3];
}

const int sceneNode::getIndex() {
	return _index;
}

void sceneNode::setIndex(int index) {
	_index = index;
}


const qtrn sceneNode::getRotQtrn() {
	return _q;
}

void sceneNode::setRotQtrn(const qtrn& q) {
	 _q = q;
}

void sceneNode::addNode(sceneNode* node) {
	node->setModelMatrix(_modelMatrix * node->getModelMatrix());
	_nodes.push_back(node);
}

const std::vector<sceneNode*> sceneNode::getNodes() {
	return _nodes;
}

void sceneNode::draw(camera& cam, GLuint indexSelected) {
	if (_shader != nullptr) {
		glUseProgram(_shader->getProgramId());

		glProgramUniform4fv(_shader->getProgramId(), _shader->getColorId(), 1, _color);
		
		matrix4x4 mM = _modelMatrix;
		glUniformMatrix4fv(_shader->getModelMatrix_UId(), 1, GL_TRUE, mM.data()); // need to be trasposed
		matrix4x4 vM = cam.getViewMatrix();
		glUniformMatrix4fv(_shader->getViewMatrix_UId(), 1, GL_FALSE, vM.data());
		matrix4x4 mP = cam.getPrespMatrix();
		glUniformMatrix4fv(_shader->getProjectionMatrix_UId(), 1, GL_FALSE, mP.data());
	}
	if (_mesh != nullptr) {
		if (_index == 0) { //table
			glStencilFunc(GL_ALWAYS, _index, 0x00);
			glStencilMask(0x00);
		}
		else if (_index > 0) {
			glStencilFunc(GL_ALWAYS, _index, 0xFF);
			glStencilMask(0xFF);
		}
		else {
			std::cout << "Error: Mesh with no index, name: " + _name << "\n";
		}
		_mesh->draw();
		if (_index == indexSelected && indexSelected >= 1 && indexSelected <= 7) { // that node was selected
			matrixFactory mf;
			glStencilFunc(GL_NOTEQUAL, _index, 0xFF);
			glStencilMask(0x00);
			glDisable(GL_DEPTH_TEST);
			
			qtrn default_qtrn = { 1.0f, 0.0f, 0.0f, 0.0f }; //DEFAULT_QTRN
			matrix4x4 R;
			if (_q == default_qtrn) { //if are equal the user did not rotate the piece 
				vector3 vR = _rotationVector;
				double angle = _angle;

				R = mf.rotationMatrix4x4(vR, angle);
			}
			else {
				matrix4x4 mAux;
				R = qGLMatrix(_q, mAux);  // matrix rotação devolve em row major
			}

			vector3 vT = _translationVector;
			matrix4x4 T = mf.translationMatrix4x4(vT);

			vector3 vS = _scalingVector * 1.1;
			matrix4x4 S = mf.scalingMatrix4x4(vS); // matrix escala

			glUseProgram(_shader->getProgramId());

			glProgramUniform4fv(_shader->getProgramId(), _shader->getColorId(), 1, _color);
			
			//glProgramUniform4fv(_shader->getProgramId(), _shader, 1, x);
			matrix4x4 mM = (T * R * S);
			glUniformMatrix4fv(_shader->getModelMatrix_UId(), 1, GL_TRUE, mM.data()); // need to be trasposed
			matrix4x4 vM = cam.getViewMatrix();
			glUniformMatrix4fv(_shader->getViewMatrix_UId(), 1, GL_FALSE, vM.data());
			matrix4x4 mP = cam.getPrespMatrix();
			glUniformMatrix4fv(_shader->getProjectionMatrix_UId(), 1, GL_FALSE, mP.data());

			_mesh->draw();
			
			glStencilMask(0xFF);
			glEnable(GL_DEPTH_TEST);
		}
	}
	for (int i = 0; i < _nodes.size(); i++) {
		sceneNode* nextNode = _nodes[i];
		matrix4x4 nextNodeModelMatrix = nextNode->getModelMatrix();
		nextNode->draw(cam, indexSelected);
	}
	
}