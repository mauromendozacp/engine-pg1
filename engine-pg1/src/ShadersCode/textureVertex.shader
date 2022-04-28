#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
layout (location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    FragPos = (model * vec4(aPos, 1.0f)).xyz;
    TexCoord = aTex;
    Normal = mat3(transpose(inverse(model))) * aNor;

    gl_Position = projection * view * vec4(FragPos, 1.0f);
}