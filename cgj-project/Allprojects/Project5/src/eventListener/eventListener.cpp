//#include "eventListener.h"
//
//void keyboard_down(unsigned char key, int x, int y) {
//	switch (key) {
//
//	}
//}
//
//void mouseWheel(int wheel, int direction, int x, int y) {
//	if (direction == -1) {
//		vector3 newEye(c.getEye()._a, c.getEye()._b, c.getEye()._c - 1);
//		c.setEye(newEye);
//		c.makeViewMatrix(newEye, c.getCenter(), c.getUp());
//	}
//	if (direction == 1) {
//		vector3 newEye(c.getEye()._a, c.getEye()._b, c.getEye()._c + 1);
//		c.setEye(newEye);
//		c.makeViewMatrix(newEye, c.getCenter(), c.getUp());
//	}
//
//
//}
//
//void OnMouseDown(int button, int state, int x, int y) {
//	// Rotate the image
//	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//		g_rot = true;
//		g_oldX = x;
//		g_oldY = y;
//	}
//	// Camera 
//	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
//
//	}
//
//}
//
//
//void OnMouseMove(int x, int y) {
//	if (g_rot == true) {
//		float tetaX = (x - g_oldX); // angle to rotate in x (Deg)
//		float tetaY = (y - g_oldY); // angle to rotate in y (Deg)
//		g_oldX = (float)x;
//		g_oldY = (float)y;
//
//		// Gimbal lock false
//		qtrn qAux;
//
//		//Recive the angle in deg
//		q = (qAux.qFromAngleAxis(tetaX, YY_4) * q);
//		q = (qAux.qFromAngleAxis(tetaY, XX_4) * q);
//
//		matrix4x4 mAux;
//		matrix4x4 mR = qGLMatrix(q, mAux);  // matrix rotação devolve em row major
//
//		vector3 vT(0, 0, -(c.getEye()._c));
//		matrix4x4 T = mf.translationMatrix4x4(vT); // matrix translação 
//
//		matrix4x4 vM = T * mR; // view matrix
//		matrix4x4 vMT = vM.transposeM4x4(); // view matrix transposta -> column major
//		c.setViewMatrix(vMT);
//	}
//}
