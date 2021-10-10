#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform vec3 color = vec3(1.0f, 1.0f, 1.0f);
uniform float a = 1.0f;
uniform sampler2D ourTexture;

void main()
{
    vec4 texColor = texture(ourTexture, TexCoord);
    if(texColor.a < 0.1f)
    {
        discard;
    }
    FragColor = texColor * vec4(ourColor.x * color.x, ourColor.y * color.y, ourColor.z * color.z, a);
}