#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

#include "matrix.h"
#include "vector.h"

void matrix2x2Test(matrix2x2 m1, matrix2x2 m2) {
	std::cout << "Starting teste matrix 2x2\n";

	std::tuple<float, float> t1 = std::make_tuple(1, 3);
	std::tuple<float, float> t2 = std::make_tuple(2, 4);
	matrix2x2 m3(t1, t2);

	m1.matrixPrint();
	m2.matrixPrint();
	m3.matrixPrint();

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
	
	matrix3x3 m3(1, 0, 5, 2, 1, 6, 3, 4, 0);
	std::cout << m3.detM3x3() << "\n";
	matrix3x3 v2 = m3.inverseM3x3();
	v2.matrixPrint();

	std::cout << "End tests of matrix 3x3\n";
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

	std::cout << "End test matrix.cpp\n";
}