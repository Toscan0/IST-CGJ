#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <assert.h>     /* assert */

#include "matrix.h"
#include "vector.h"

void matrix2x2Test(matrix2x2 m1, matrix2x2 m2) {
	std::cout << "Starting teste matrix 2x2\n";

	m1.matrixPrint(); // (1,2,3,4)
	m2.matrixPrint(); // (1,2,3,4)

	bool x = m1 == m2; //true -> 1
	assert(x == 1);

	matrix2x2 aux1 = m1 + m2; //(2,4,6,8)
	matrix2x2 mx1(2, 4, 6, 8);
	assert(aux1 == mx1);
	
	matrix2x2 aux2 = m1 - m2; //(0,0,0,0)
	matrix2x2 mx2(0, 0, 0, 0);
	assert(aux2 == mx2);

	matrix2x2 aux3 = m1 * m2; //(7, 10, 15, 22)
	matrix2x2 mx3 (7, 10, 15, 22);
	assert(aux3 == mx3);

	matrix2x2 aux4 = m1 * (-0.5); //(-0.5, -1, -1.5, -2)
	matrix2x2 mx4(-0.5, -1, -1.5, -2);
	assert(aux4 == mx4);

	vector2 v(6, 6);
	vector2 aux5 = m1 * v; // (18, 42)
	vector2 vx5(18, 42);
	assert(aux5 == vx5);

	matrix2x2 aux6 = m1.transposeM2x2(); // (1, 3, 2, 4)
	matrix2x2 mx6 (1, 3, 2, 4);
	assert(aux6 == mx6);

	float det = m1.detM2x2(); // -2
	assert(det == -2);

	matrix2x2 aux7 = m1.inverseM2x2(); // (-2, 1, 1.5 , -0.5)
	matrix2x2 mx7 (-2, 1, 1.5, -0.5);
	assert(aux7 == mx7);

	std::cout << "End tests of matrix 2x2\n";
}

void matrix3x3Test(matrix3x3 m1, matrix3x3 m2) {
	std::cout << "Starting teste matrix 3x3\n";

	m1.matrixPrint(); // (1,2,3,4, 5, 6, 7, 8, 9)
	m2.matrixPrint(); // (1,2,3,4, 5, 6, 7, 8, 9)

	bool x = m1 == m2; //true -> 1
	assert(x == 1);

	matrix3x3 aux1 = m1 + m2; // (2, 4, 6, 8, 10, 12, 14, 16, 18)
	matrix3x3 mx1(2, 4, 6, 8, 10, 12, 14, 16, 18);
	assert(aux1 == mx1);

	matrix3x3 aux2 = m1 - m2; // (0, 0, 0, 0, 0, 0, 0, 0, 0)
	matrix3x3 mx2 (0, 0, 0, 0, 0, 0, 0, 0, 0);
	assert(aux2 == mx2);
	
	matrix3x3 aux3 = m1 * m2; // (30, 36, 42, 66, 81, 96, 102, 126, 150)
	matrix3x3 mx3 (30, 36, 42, 66, 81, 96, 102, 126, 150);
	assert(aux3 == mx3);

	matrix3x3 aux4 = m1 * (-0.5); //(-0.5, -1, -1.5, -2, -2.5, -3, -3.5, -4, -4.5)
	matrix3x3 mx4 (-0.5, -1, -1.5, -2, -2.5, -3, -3.5, -4, -4.5);
	assert (aux4 == mx4);
	
	vector3 v (6, 6, 6);
	vector3 aux5 = m1 * v; // (36, 90, 144)
	vector3 vx5 (36, 90, 144);
	assert (aux5 == vx5);

	matrix3x3 aux6 = m1.transposeM3x3(); // (1, 4, 7, 2, 5, 8, 3, 6, 9)
	matrix3x3 mx6 (1, 4, 7, 2, 5, 8, 3, 6, 9);
	assert(aux6 == mx6);

	matrix3x3 m3(1, 2, 3, 0, 1, 4, 5, 6, 9);

	float det = m3.detM3x3(); // 10
	assert(det == 10);

	matrix3x3 aux7 = m3.inverseM3x3(); // (-1.5, 0, 0.5, 2, -0.6, -0.4, -0.5, 0.4, 0.1)
	matrix3x3 mx7(-1.5, 0, 0.5, 2, -0.6, -0.4, -0.5, 0.4, 0.1);
	aux7.matrixPrint();
	mx7.matrixPrint();
	assert(aux7 == mx7);

	std::cout << "End tests of matrix 3x3\n";
}


void matrix4x4Test(matrix4x4 m1, matrix4x4 m2) {
	std::cout << "Starting teste matrix 4x4\n";

	m1.matrixPrint(); // (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)
	m2.matrixPrint(); // (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)
	
	bool x = m1 == m2; //true -> 1
	assert(x == 1);

	matrix4x4 aux1 = m1 + m2; // (2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32)
	matrix4x4 mx1(2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32);
	assert(aux1 == mx1);

	matrix4x4 aux2 = m1 - m2; // (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
	matrix4x4 mx2(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	assert(aux2 == mx2);

	matrix4x4 aux3 = m1 * m2; // (90, 100, 110, 120, 202, 228, 254, 280, 314, 356, 398, 440, 426, 484, 542, 600)
	matrix4x4 mx3 (90, 100, 110, 120, 202, 228, 254, 280, 314, 356, 398, 440, 426, 484, 542, 600);
	assert(aux3 == mx3);
	
	matrix4x4 aux4 = m1 * (-0.5); //(-0.5, -1, -1.5, -2, -2.5, -3, -3.5, -4, -4.5, -5, -5.5, -6, -6.5, -7, -7.5, -8)
	matrix4x4 mx4(-0.5, -1, -1.5, -2, -2.5, -3, -3.5, -4, -4.5, -5, -5.5, -6, -6.5, -7, -7.5, -8);
	assert(aux4 == mx4);
		
	vector4 v (6, 6, 6, 6);
	vector4 aux5 = m1 * v; // (60, 156, 252, 348)
	vector4 vx5 (60, 156, 252, 348);
	assert(aux5 == vx5);
	
	matrix4x4 aux6 = m1.transposeM4x4(); // (1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16)
	matrix4x4 mx6(1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16);
	assert(aux6 == mx6);

	float det = m1.detM4x4(); // 0
	assert(det == 0);

	std::cout << "End tests of matrix 4x4\n";
}
void callMatrixTests() {
	std::cout << "\n";
	std::cout << "Starting test matrix.cpp\n";

	// matrix 2x2
	matrix2x2 m1(1, 2, 3, 4);
	vector2 v1 (1, 3);
	vector2 v2(2, 4);
	matrix2x2 m2 (v1, v2);
	matrix2x2Test(m1, m2);
	
	// matrix 3x3
	matrix3x3 m3 (1, 2, 3, 4, 5, 6, 7, 8, 9);
	vector3 v3 (1, 4, 7);
	vector3 v4 (2, 5, 8);
	vector3 v5 (3, 6, 9);
	matrix3x3 m4 (v3, v4, v5);
	matrix3x3Test(m3, m4);

	// matrix 4x4
	matrix4x4 m5 (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	vector4 v6 (1, 5, 9, 13);
	vector4 v7 (2, 6, 10, 14);
	vector4 v8 (3, 7, 11, 15);
	vector4 v9(4, 8, 12, 16);
	matrix4x4 m6 (v6, v7, v8, v9);
	matrix4x4Test (m5, m6);

	std::cout << "End test matrix.cpp\n";
}