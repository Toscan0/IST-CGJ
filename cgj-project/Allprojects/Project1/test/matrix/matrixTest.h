#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <assert.h>     /* assert */

#include "../../src/matrix/matrix2x2/matrix2x2.h"
#include "../../src/matrix/matrix3x3/matrix3x3.h"
#include "../../src/matrix/matrix4x4/matrix4x4.h"

void matrix2x2Test(matrix2x2, matrix2x2);

void matrix3x3Test(matrix3x3, matrix3x3);

void matrix4x4Test(matrix4x4, matrix4x4);


void callMatrixTests();