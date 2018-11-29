#version 330 core 

in vec3 exNormal;
out vec4 out_color; 

void main(void) 
{ 
	out_color = vec4((vec3(1,1,1) + exNormal) * (0.5), 1);
}