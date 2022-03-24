#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform vec3 baseColor;
uniform float a;
uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord) * vec4(baseColor, a);
}