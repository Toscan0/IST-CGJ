#version 330 core 

// data from vertex shader
in vec3 exNormal;
in vec2 exTexcoord;
in vec3 exLight;
in vec3 exCamera;

// color for framebuffer
out vec4 out_color; 

// texture with diffuese color of the object
uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;

/////////////////////////////////////////////////////////

// parameters of the light and possible values
uniform vec3 lightAmbientIntensity = vec3(0.6, 0.3, 0);
uniform vec3 lightDiffuseIntensity = vec3(1, 0.5, 0);
uniform vec3 lightSpecularIntensity = vec3(1, 1, 1);

// parameters of the material and possible values
uniform vec3 matAmbientReflectance = vec3(1, 1, 1);
uniform vec3 matDiffuseReflectance = vec3(1, 1, 1);
uniform vec3 matSpecularReflectance = vec3(0.5, 0.5, 0.5);
uniform float matShininess = 62;

/////////////////////////////////////////////////////////

// returns intensity of reflected ambient lighting
vec3 ambientLighting()
{
   return matAmbientReflectance * lightAmbientIntensity;
}

// returns intensity of diffuse reflection
vec3 diffuseLighting(in vec3 N, in vec3 L)
{
   // calculation as for Lambertian reflection
   float diffuseTerm = clamp(dot(N, L), 0, 1) ;
   return matDiffuseReflectance * lightDiffuseIntensity * diffuseTerm;
}

// returns intensity of specular reflection
vec3 specularLighting(in vec3 N, in vec3 L, in vec3 V)
{
   float specularTerm = 0;

   // calculate specular reflection only if
   // the surface is oriented to the light source
   if(dot(N, L) > 0)
   {
      // half vector
      vec3 H = normalize(L + V);
      specularTerm = pow(max(dot(N, H), 0.0), matShininess);
   }
   return matSpecularReflectance * lightSpecularIntensity * specularTerm;
}

void main(void)
{
   // normalize vectors after interpolation
   vec3 L = normalize(exLight);
   vec3 V = normalize(exCamera);
   //vec3 N = normalize(exNormal);

   // Local normal, in tangent space [0-1]
   vec3 N = normalize(texture(normalTexture, exTexcoord).rgb*2.0 - 1.0);

   // get Blinn-Phong reflectance components
   vec3 Iamb = ambientLighting();
   vec3 Idif = diffuseLighting(N, L);
   vec3 Ispe = specularLighting(N, L, V);

   // diffuse color of the object from texture
   vec3 diffuseColor = texture(diffuseTexture, exTexcoord).rgb;

   // combination of all components and diffuse color of the object
   out_color.xyz = diffuseColor * (Iamb + Idif + Ispe);
   out_color.a = 1;
}