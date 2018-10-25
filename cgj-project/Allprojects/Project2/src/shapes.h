#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "Vertex.h"
#include  "matrix/matrix4x4/matrix4x4.h"

// --------------------- Vertices -------------------------------
// Small right triangle
const Vertex VerticesSTri[] =
{
	{{-0.125f, -0.125f, 0.0f, 1.0f }},
	{{ 0.125f, -0.125f, 0.0f, 1.0f }},
	{{-0.125f,  0.125f, 0.0f, 1.0f }},
};

const GLubyte IndicesSTri[] =
{
	0,1,2, 2,1,0
};

// Squad 
const Vertex VerticesSquare[] =
{
	{{-0.125f, -0.125f, 0.0f, 1.0f}},
	{{ 0.125f, -0.125f, 0.0f, 1.0f}},
	{{-0.125f,  0.125f, 0.0f, 1.0f}},
	{{ 0.125f,  0.125f, 0.0f, 1.0f}},
};

const GLubyte IndicesSquare[] =
{
	0,1,2,2,1,3, 3,1,2,2,1,0
};

// Parallelogram 
const Vertex VerticesParall[] =
{
	{{-0.125f, -0.125f, 0.0f, 1.0f}},
	{{ 0.125f, -0.125f, 0.0f, 1.0f}},
	{{-0.0f,  0.125f, 0.0f, 1.0f}},
	{{ 0.25f,  0.125f, 0.0f, 1.0f}},
};

const GLubyte IndicesParall[] =
{
	0,1,2,2,1,3, 3,1,2,2,1,0
};

// --------------------- Matrix -------------------------------
typedef GLfloat Matrix[16];
Matrix I, M1, M2, M3, M4, M5, M6, M7;
// pass the small triangle to a Large triangle
matrix4x4 mL(2.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 2.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 2.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.5f);

// --------------------- Colors -------------------------------
float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float yellow[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
float purple[4] = { 0.8f, 0.0f, 0.2f, 1.0f };
float pink[4] = { 1.0f, 0.5f, 0.5f, 1.0f };

