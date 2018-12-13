#version 330 core 

in vec3 exNormal;

in vec4 ex_Color;
out vec4 out_color; 

uniform vec4 color;

void main(void) 
{ 
	out_color = color;
}