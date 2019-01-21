#version 330 core

// attributes
in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;
in vec3 inTangent;
in vec3 inBitangent;

// data for fragment shader
out vec3 exNormal;
out vec2 exTexcoord;
out vec3 exLight;
out vec3 exCamera;

// matrices
uniform mat4 ModelMatrix;
uniform	mat4 ViewMatrix;
uniform	mat4 ProjectionMatrix;
//uniform mat3 NormalMatrix;

// position of light and camera
uniform vec3 lightPosition;

void main(void)
{
	mat3 normalMatrix = transpose(inverse(mat3(ViewMatrix * ModelMatrix)));
	vec4 wPosition = ModelMatrix * vec4(inPosition, 1);
	// position in view space
	vec4 vPosition	= ViewMatrix * ModelMatrix * vec4(inPosition, 1);

	// normal in view space
	exNormal = normalMatrix * inNormal;

	// tangent in view space
	vec3 vTangent = (ViewMatrix * ModelMatrix * vec4(inTangent, 1)).xyz;

	// bitangent in view space
	vec3 vBitangent = (ViewMatrix * ModelMatrix * vec4(inBitangent, 1)).xyz;

	// TBN inverse
	mat3 TBN = transpose(mat3(vTangent, vBitangent, exNormal));

	// direction to light
	vec4 vLightPosition = ViewMatrix * vec4(lightPosition, 1);
	exLight = TBN * (vLightPosition.xyz - vPosition.xyz);

	// direction to camera
	exCamera = TBN * (- vPosition.xyz);

	// texture coordinates to fragment shader
	exTexcoord = inTexcoord;
	
	// screen space coordinates of the vertex
	gl_Position = ProjectionMatrix * vPosition;
}