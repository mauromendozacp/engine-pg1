#version 330 core
out vec4 FragColor;
in vec3 ourColor;

uniform vec3 color = vec3(1.0f, 1.0f, 1.0f);

uniform float a = 1.0f;

void main()
{
   FragColor = vec4(color.x, color.y, color.z, a);
}