#version 330 core
out vec4 FragColor;

uniform vec3 baseColor;
uniform vec3 lightColor;

uniform float a;

void main()
{
	FragColor = vec4(baseColor * lightColor, a);
}