#include "av1.h"

bool ex1() {
	// i * (j*k) == j*(i*k)-k(i*j)

	vector3 vx(makeRandom(), makeRandom(), makeRandom()); // i
	vector3 vy(makeRandom(), makeRandom(), makeRandom()); // j
	vector3 vz(makeRandom(), makeRandom(), makeRandom()); // k

	vector3 v1 = cross(vx, (cross(vy, vz)));
	//v1.printVc3();

	vector3 v2 = (vy * (dot(vx, vz))) - (vz * (dot(vx, vy)));
	//v2.printVc3();

	bool x = (v1 == v2);

	return x;
}


vector3 ex2(vector3& v, vector3& a, double x) {
	matrixFactory mF;
	matrix3x3 m = mF.rodriguez(a, x);

	vector3 vr = m * v;

	return vr;
}


void callV1Test() {
	bool res1 = ex1();
	std::cout << "res1 " << (res1) << "\n";

	vector3 xx(2, 0, 0); // v
	vector3 yy(0, 3, 0); // a
	double teta = 3.141592 / 2;
	vector3 n = yy.normalizado();

	vector3 res2_1 = ex2(xx, n, teta);
	vector3 v2(0, 0, -2);
	bool x_1 = (res2_1 == v2);
	std::cout << x_1 << "\n";


	vector3 res2_2 = ex2(xx, n, -teta);
	vector3 v3(0, 0, 2);
	bool x_2 = (res2_2 == v3);
	std::cout << x_2 << "\n";

	matrix3x3 m(1, 1, 1, 1, 1, 1, 1, 1, 1);

	matrix3x3 m_1 = m * 2.0f;
	m_1.matrixPrint();

	matrix3x3 m_2 = 2.0f*m;
	m_2.matrixPrint();
}