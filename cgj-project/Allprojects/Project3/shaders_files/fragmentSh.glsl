#version 330 core

uniform vec4 color;

in vec4 ex_Color;
out vec4 out_Color;


void main(void)
{
	out_Color = color;
}