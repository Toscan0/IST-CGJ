#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include "src/vector/vector4/vector4.h"
#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913

/////////////////////////////////////////////////////////////////////// mat4

typedef float mat4[16]; // column major
const float mThreshold = (float)1.0e-5;

const vector4 mMultiply(mat4 m, vector4& v);
const void mClean(mat4 m);
const void mPrint(const std::string s, const mat4 m);