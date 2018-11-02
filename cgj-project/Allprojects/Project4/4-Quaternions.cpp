///////////////////////////////////////////////////////////////////////
//
// Using quaternions to rotate in 3D.
//
// Assignment: 1. Create a class for Quaternions.
//             2. Create a scene with a camera rotating around an 
//                object at the origin and pointing towards it. 
//                Do NOT use "gluLookAt" to create the ViewMatrix, 
//                use rotation matrices!
//             3. Gimbal lock mode ON: use Translation + Rotation 
//                matrices (e.g. Euler angles, Rodrigues’ formula).
//             4. Gimbal lock mode OFF: use Quaternions to produce a 
//                transformation matrix and avoid gimbal lock.
//             5. Switch between modes by pressing the 'g' key.
//
// (c) 2013-18 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>

#include "qtrn.h"

#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913

///////////////////////////////////////////////////////////////////////

#define HEADER(X) std::cout<<std::endl<<(X)<<std::endl<<std::endl;

void qtest1()
{
	HEADER("TEST 1 : Rotation of 90 degrees about the y-axis");

	vector4 axis = { 0.0f, 1.0f, 0.0f, 1.0f };
	qtrn qAux;
	qtrn q = qAux.qFromAngleAxis(90.0f, axis);
	qPrint("   q", q);

	qtrn vi = { 0.0f, 7.0f, 0.0f, 0.0f };
	qPrint("  vi", vi);

	qtrn qe = { 0.0f, 0.0f, 0.0f, -7.0f };
	qPrint("  qe", qe);

	qtrn qinv = qInverse(q);
	qAux.qClean(qinv);
	qPrint("qinv", qinv);

	qtrn qf = ((q * vi) * qinv);
	qPrint("  qf", qf);

	assert((qf == qe));
}

void qtest2()
{
	HEADER("TEST 2 : Rotation of 90 degrees about the y-axis with matrix");

	vector4 axis = { 0.0f, 1.0f, 0.0f, 1.0f };
	qtrn qAux;
	qtrn q = qAux.qFromAngleAxis(90.0f, axis);
	qPrint(" q", q);

	vector4 vi = { 7.0f, 0.0f, 0.0f, 1.0f };
	vPrint("vi", vi);

	vector4 ve = { 0.0f, 0.0f, -7.0f, 1.0f };
	vPrint("ve", ve);

	matrix4x4 m;
	matrix4x4 mAux = qGLMatrix(q, m);
	mPrint(" M", mAux);

	vector4 vf = mMultiply(mAux, vi);
	vPrint("vf", vf);

	assert(vEqual(vf, ve));
}

void qtest3()
{
	HEADER("TEST 3 : Yaw 900 = Roll 180 + Pitch 180");
	qtrn qAux;
	vector4 axis_x = { 1.0f, 0.0f, 0.0f, 1.0f };
	vector4 axis_y = { 0.0f, 1.0f, 0.0f, 1.0f };
	vector4 axis_z = { 0.0f, 0.0f, 1.0f, 1.0f };

	qtrn qyaw900 = qAux.qFromAngleAxis(900.0f, axis_y);
	qPrint("  qyaw900", qyaw900);

	qtrn qroll180 = qAux.qFromAngleAxis(180.0f, axis_x);
	qPrint(" qroll180", qroll180);
	qtrn qpitch180 = qAux.qFromAngleAxis(180.0f, axis_z);
	qPrint("qpitch180", qpitch180);
	qtrn qrp = (qpitch180 * qroll180);
	qPrint("      qrp", qrp);
	qtrn qpr = (qroll180 * qpitch180);
	qPrint("      qpr", qpr);

	qtrn qi = { 0.0f, 1.0f, 0.0f, 0.0f }; // x-axis
	qPrint("       qi", qi);
	qtrn qe = { 0.0f, -1.0f, 0.0f, 0.0f };
	qPrint("       qe", qe);

	qtrn qyaw900inv = qInverse(qyaw900);
	qtrn qfy = ((qyaw900 *  qi) * qyaw900inv);
	qPrint("       qy", qfy);
	assert((qe == qfy));

	qtrn qrpinv = qInverse(qrp);
	qtrn qfrp = ((qrp * qi) * qrpinv);
	qPrint("     qfrp", qfrp);
	assert((qe == qfrp));

	qtrn qprinv = qInverse(qpr);
	qtrn qfpr = ((qpr * qi) * qprinv);
	qPrint("     qfpr", qfpr);
	assert((qe == qfpr));
}

void qtest4()
{
	HEADER("TEST 4: Q <-> (angle, axis)");
	qtrn qAux;
	float thetai = 45.0f;
	vector4 axis_i = { 0.0f, 1.0f, 0.0f, 1.0f };
	qtrn q = qAux.qFromAngleAxis(thetai, axis_i);
	std::cout << thetai << " ";
	vPrint("axis_i", axis_i);

	float thetaf;
	vector4 axis_f;
	qAux.qToAngleAxis(q, thetaf, axis_f);
	std::cout << thetaf << " ";
	vPrint("axis_f", axis_f);
	float qThreshold = qAux.getQThreshold();
	assert(fabs(thetai - thetaf) < qThreshold && vEqual(axis_i, axis_f));
}

void qtest5()
{
	HEADER("TEST 5: LERP");

	vector4 axis = { 0.0f, 1.0f, 0.0f, 1.0f };
	qtrn qAux;
	qtrn q0 = qAux.qFromAngleAxis(0.0f, axis);
	qPrint("       q0", q0);
	qtrn q1 = qAux.qFromAngleAxis(90.0f, axis);
	qPrint("       q1", q1);
	qtrn qe = qAux.qFromAngleAxis(30.0f, axis);
	qPrint("       qe", qe);

	qtrn qLerp0 = qAux.qLerp(q0, q1, 0.0f);
	qPrint("  lerp(0)", qLerp0);
	assert((qLerp0 == q0));

	qtrn qLerp1 = qAux.qLerp(q0, q1, 1.0f);
	qPrint("  lerp(1)", qLerp1);
	assert((qLerp1 == q1));

	qtrn qlerp = qAux.qLerp(q0, q1, 1 / 3.0f);
	qPrint("lerp(1/3)", qlerp);
	qAux.qPrintAngleAxis("lerp(1/3)", qlerp);

	assert((qlerp == qe) == 0);
}

void qtest6()
{
	HEADER("TEST 6: SLERP");
	qtrn qAux;
	vector4 axis = { 0.0f, 1.0f, 0.0f, 1.0f };
	qtrn q0 = qAux.qFromAngleAxis(0.0f, axis);
	qPrint("        q0", q0);
	qtrn q1 = qAux.qFromAngleAxis(90.0f, axis);
	qPrint("        q1", q1);
	qtrn qe = qAux.qFromAngleAxis(30.0f, axis);
	qPrint("        qe", qe);

	qtrn qSlerp0 = qAux.qSlerp(q0, q1, 0.0f);
	qPrint("  slerp(0)", qSlerp0);
	assert((qSlerp0 == q0));

	qtrn qSlerp1 = qAux.qSlerp(q0, q1, 1.0f);
	qPrint("  slerp(1)", qSlerp1);
	assert((qSlerp1 == q1));

	qtrn qslerp = qAux.qSlerp(q0, q1, 1 / 3.0f);
	qPrint("slerp(1/3)", qslerp);
	qAux.qPrintAngleAxis("slerp(1/3)", qslerp);

	assert((qslerp == qe));
}

///////////////////////////////////////////////////////////////////////
/** /
int main(int argc, char* argv[])
{
	qtest1();
	qtest2();
	qtest3();
	qtest4();
	qtest5();
	qtest6();

	std::cout << std::endl << "Press <return>.";
	std::cin.ignore(1);
	exit(EXIT_SUCCESS);
}
/**/

///////////////////////////////////////////////////////////////////////