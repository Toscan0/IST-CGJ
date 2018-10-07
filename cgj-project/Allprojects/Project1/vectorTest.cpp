#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

#include "vector.h"


int vector2Test(vector2 v1, vector2 v2) {
	std::cout << "Starting teste vector2\n";
	
	v1.printVc2(); //(5, 4)
	v2.printVc2();//(5,3)
	bool x = v1 == v2;
	std::cout << x << "\n"; //0 -> false
	vector2 aux1 = v1 + v2;
	aux1.printVc2(); //(10, 7)
	vector2 aux2 = v1 - v2;
	aux2.printVc2(); //(0, 1)
	vector2 aux3 = v1 * 2;
	aux3.printVc2(); //(10, 8)

	std::cout << "End tests of vector2\n";

	return 0;
}

int vector3Test(vector3 v1, vector3 v2) {
	std::cout << "Starting teste vector3\n";

	v1.printVc3(); //(1, 2, 3)
	v2.printVc3();//(4, 5, 6)
	bool x = v1 == v2;
	std::cout << x << "\n"; //0 -> false
	vector3 aux1 = v1 + v2;
	aux1.printVc3(); //(5, 7, 9)
	vector3 aux2 = v1 - v2;
	aux2.printVc3(); //(-3, -3, -3)
	vector3 aux3 = v1 * 2;
	aux3.printVc3(); //(2, 4, 6)
	int y = v1.dotProductVc3(v2);
	std::cout << y << "\n"; //32
	vector3 aux4 = v1.crossProductVc3(v2);
	aux4.printVc3(); //(-3, 6, -3)

	std::cout << "End tests of vector3\n";

	return 0;
}

int vector4Test(vector4 v1, vector4 v2) {
	std::cout << "Starting teste vector4\n";

	v1.printVc4(); //(1, 2, 3, 4)
	v2.printVc4(); //(5, 6, 7, 8)
	bool x = v1 == v2;
	std::cout << x << "\n"; //0 -> false
	vector4 aux1 = v1 + v2;
	aux1.printVc4(); //(6, 8, 10, 12)
	vector4 aux2 = v1 - v2;
	aux2.printVc4(); //(-4, -4, -4, -4)
	vector4 aux3 = v1 * 2;
	aux3.printVc4(); //(2, 4, 6, 8)

	std::cout << "End tests of vector4\n";

	return 0;
}

void callTests() {
	vector2 v1 (5, 4);
	std::tuple<float, float> t1 = std::make_tuple(5, 3);
	vector2 v2 (t1);
	
	vector2Test(v1, v2);

	vector3 v3(1, 2, 3);
	std::tuple<float, float, float> t2 = std::make_tuple(4, 5, 6);
	vector3 v4(t2);
	
	vector3Test(v3, v4);

	vector4 v5(1, 2, 3, 4);
	std::tuple<float, float, float, float> t3 = std::make_tuple(5, 6, 7, 8);
	vector4 v6(t3);

	vector4Test(v5, v6);
}