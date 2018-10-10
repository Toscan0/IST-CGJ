#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <assert.h>     /* assert */

#include "matrix.h"
#include "vector.h"

void matrix2x2Test(matrix2x2 m1, matrix2x2 m2) {
	std::cout << "Starting teste matrix 2x2\n";

	m1.matrixPrint();
	m2.matrixPrint();

	matrix2x2 aux1 = m1 + m2;
	aux1.matrixPrint(); 

	matrix2x2 aux2 = m1 - m2;
	aux2.matrixPrint();

	matrix2x2 aux3 = m1 * m2;
	aux3.matrixPrint();

	matrix2x2 aux4 = m1 * (-0.5);
	aux4.matrixPrint();

	matrix2x2 aux5 = m1.transposeM2x2();
	aux5.matrixPrint();

	matrix2x2 aux9 = m1.inverseM2x2();
	aux9.matrixPrint();

	std::cout << "End tests of matrix 2x2\n";
}

void matrix3x3Test(matrix3x3 m1, matrix3x3 m2) {
	std::cout << "Starting teste matrix 3x3\n";

	matrix3x3 v = m1.transposeM3x3();
	v.matrixPrint();
	
	matrix3x3 m3(1, 2, 3, 0, 1, 4, 5, 6, 0);
	std::cout << m3.detM3x3() << "çççç\n";
	matrix3x3 v2 = m3.inverseM3x3();
	v2.matrixPrint();

	std::cout << "End tests of matrix 3x3\n";
}


void matrix4x4Test(matrix4x4 m1, matrix4x4 m2) {
	std::cout << "Starting teste matrix 4x4\n";

	m1.matrixPrint();

	bool b = m1 == m1;
	std::cout << b << "\n"; //1

	matrix4x4 aux1 = m1 + m1;
	aux1.matrixPrint();

	matrix4x4 aux2 = m1 - m1;
	aux2.matrixPrint();

	std::cout << "--\n";
	matrix4x4 aux3 = m1 * m1;
	aux3.matrixPrint();

	matrix4x4 aux4 = m1 * 2;
	aux4.matrixPrint();
	
	float l = m1.detM4x4();
	std::cout << "det" << l << "\n";
	
	matrix4x4 aux6 = m1.transposeM4x4();
	aux6.matrixPrint();

	std::cout << "End tests of matrix 4x4\n";
}
void callMatrixTests() {
	std::cout << "\n";
	std::cout << "Starting test matrix.cpp\n";

	matrix2x2 m1(1, 2, 3, 4);
	vector2 v1 (1, 3);
	vector2 v2(2, 4);
	matrix2x2 m2 (v1, v2);
	
	matrix2x2Test(m1, m2);
	

	matrix3x3 m3 (1, 2, 3, 4, 5, 6, 7, 8, 9);
	vector3 v3 (1, 2, 3);
	vector3 v4 (4, 5, 6);
	vector3 v5 (7, 8, 9);
	matrix3x3 m4 (v3, v4, v5);

	matrix3x3Test(m3, m4);

	matrix4x4 m5 (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	matrix4x4 m6 (1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);

	matrix4x4Test(m5, m6);

	std::cout << "End test matrix.cpp\n";
}