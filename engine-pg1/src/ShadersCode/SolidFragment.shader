#version 330 core
out vec4 FragColor;
in vec3 ourColor;

uniform vec3 color;

uniform float a = 1.0f;

void main()
{
	FragColor = vec4(ourColor * color, a);
}