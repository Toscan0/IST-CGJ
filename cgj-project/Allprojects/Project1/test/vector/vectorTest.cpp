#include "vectorTest.h"

int vector2Test(vector2 v1, vector2 v2) {
	std::cout << "Starting teste vector2\n";
	
	v1.printVc2(); // (5, 4)
	v2.printVc2(); // (5,3)
	
	float* v1_lst = v1.data();
	assert(v1_lst[0] == 5);
	assert(v1_lst[1] == 4);

	float* v2_lst = v2.data();
	assert(v2_lst[0] == 5);
	assert(v2_lst[1] == 3);

	vector2 v_1(5, 4);
	assert(v1 == v_1);
	
	vector2 v_2(5, 3);
	assert(v2 == v_2);

	bool x = v1 == v2; //0 -> false
	assert (x == 0);
	
	vector2 aux1 = v1 + v2; // (10, 7)
	vector2 vx1(10, 7);
	assert(aux1 == vx1);


	vector2 aux2 = v1 - v2; // (0, 1)
	vector2 vx2(0, 1);
	assert(aux2 == vx2);

	vector2 aux3 = v1 * 2; // (10, 8)
	vector2 vx3(10, 8);
	assert(aux3 == vx3);

	std::cout << "End tests of vector2\n";

	return 0;
}

int vector3Test(vector3 v1, vector3 v2) {
	std::cout << "Starting teste vector3\n";

	v1.printVc3(); //(1, 2, 3)
	v2.printVc3();//(4, 5, 6)

	float* v1_lst = v1.data();
	assert(v1_lst[0] == 1);
	assert(v1_lst[1] == 2);
	assert(v1_lst[2] == 3);

	float* v2_lst = v2.data();
	assert(v2_lst[0] == 4);
	assert(v2_lst[1] == 5);
	assert(v2_lst[2] == 6);

	bool x = v1 == v2; //0 -> false
	assert(x == 0);

	vector3 aux1 = v1 + v2; //(5, 7, 9)
	vector3 vx1(5, 7, 9);
	assert(aux1 == vx1);

	vector3 aux2 = v1 - v2; //(-3, -3, -3)
	vector3 vx2(-3, -3, -3);
	assert(aux2 == vx2);

	vector3 aux3 = v1 * 2; //(2, 4, 6)
	vector3 vx3 (2, 4, 6);
	assert(aux3 == vx3);

	int y = dot(v1, v2); //32
	assert(y == 32);

	vector3 aux4 = cross(v1, v2); //(-3, 6, -3)
	vector3 vx4 (-3, 6, -3);
	assert(aux4 == vx4);

	std::cout << "End tests of vector3\n";

	return 0;
}

int vector4Test(vector4 v1, vector4 v2) {
	std::cout << "Starting teste vector4\n";

	v1.printVc4(); //(1, 2, 3, 4)
	v2.printVc4(); //(5, 6, 7, 8)

	float* v1_lst = v1.data();
	assert(v1_lst[0] == 1);
	assert(v1_lst[1] == 2);
	assert(v1_lst[2] == 3);
	assert(v1_lst[3] == 4);

	float* v2_lst = v2.data();
	assert(v2_lst[0] == 5);
	assert(v2_lst[1] == 6);
	assert(v2_lst[2] == 7);
	assert(v2_lst[3] == 8);

	bool x = v1 == v2; //0 -> false
	assert(x == 0);

	vector4 aux1 = v1 + v2; //(6, 8, 10, 12)
	vector4 vx1(6, 8, 10, 12);
	assert(aux1 == vx1);

	vector4 aux2 = v1 - v2; //(-4, -4, -4, -4)
	vector4 vx2(-4, -4, -4, -4);
	assert(aux2 == vx2);

	vector4 aux3 = v1 * 2; //(2, 4, 6, 8)
	vector4 vx3(2, 4, 6, 8);
	assert(aux3 == vx3);

	std::cout << "End tests of vector4\n";

	return 0;
}

void callVectorTests() {
	std::cout << "\n";
	std::cout << "Starting test vector.cpp\n";
	
	//vector2
	vector2 v1 (5, 4);
	std::tuple<float, float> t1 = std::make_tuple(5, 3);
	vector2 v2 (t1);
	vector2Test(v1, v2);

	//vector3
	vector3 v3(1, 2, 3);
	std::tuple<float, float, float> t2 = std::make_tuple(4, 5, 6);
	vector3 v4(t2);
	vector3Test(v3, v4);

	//vector4
	vector4 v5(1, 2, 3, 4);
	std::tuple<float, float, float, float> t3 = std::make_tuple(5, 6, 7, 8);
	vector4 v6(t3);
	vector4Test(v5, v6);
	
	std::cout << "End vector.cpp test\n";
}