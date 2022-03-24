#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 baseColor;
uniform vec3 lightColor;
uniform float a;

uniform sampler2D ourTexture;
uniform bool useTexture;
uniform bool affectedLight;

void main()
{
	vec3 resultColor = vec3(0, 0, 0);
	if (affectedLight == true)
		resultColor = baseColor * lightColor;
	else
		resultColor = baseColor;

	if (useTexture == false)
		FragColor = vec4(resultColor, a);
	else
		FragColor = texture(ourTexture, TexCoord) * vec4(resultColor, a);
}