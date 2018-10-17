#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Vertex.h"

// Small right triangle (brown)
const Vertex VerticesSTri[] =
{
	{{ 0.0f, 0.0f, 0.0f, 1.0f }, { 0.5f, 0.2f, 0.0f, 1.0f }},
	{{ 0.25f, 0.0f, 0.0f, 1.0f }, { 0.5f, 0.2f, 0.0f, 1.0f }},
	{{ 0.0f, 0.25f, 0.0f, 1.0f }, { 0.5f, 0.2f, 0.0f, 1.0f }},
};

const GLubyte IndicesSTri[] =
{
	0,1,2
};

// Squad (yellow)
const Vertex VerticesSquare[] =
{
	{{ -0.25f, -0.25f, 0.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }},
	{{ 0.25f, -0.25f, 0.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }},
	{{ -0.25f, 0.25f, 0.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }},
	{{ 0.25f, 0.25f, 0.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }},
};

const GLubyte IndicesSquare[] =
{
	0,1,2,2,1,3
};

// Parallelogram (blue)
const Vertex VerticesParall[] =
{
	{{ -0.25f, -0.25f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }},
	{{ 0.25f, -0.25f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }},
	{{ -0.13f, 0.25f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }},
	{{ 0.38f, 0.25f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }},
};

const GLubyte IndicesParall[] =
{
	0,1,2,2,1,3
};

