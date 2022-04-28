#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;

void main()
{
    FragPos = (model * vec4(aPos, 1.0f)).xyz;
    Normal = mat3(transpose(inverse(model))) * aNor;

    gl_Position = projection * view * vec4(FragPos, 1.0f);
}