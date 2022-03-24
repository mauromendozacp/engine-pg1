#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

struct Light
{
	vec3 color;
	bool enabled;
};

struct DirectionalLight
{
	vec3 color;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	bool enabled;
};

struct PointLight {
	vec3 color;
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
	float linear;
	float quadratic;
	bool enabled;
};

uniform vec3 color;
uniform float a;

uniform Light light;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;

uniform sampler2D ourTexture;
uniform bool useTexture;
uniform bool affectedLight;
uniform vec3 viewPosition;

vec3 CalculateDirLight();

void main()
{
	vec3 resultColor = vec3(0.0f, 0.0f, 0.0f);
	if (affectedLight == true)
	{
		if (light.enabled == true)
		{
			resultColor = color * light.color;
		}
		if (directionalLight.enabled == true)
		{
			resultColor += CalculateDirLight();
		}
	}
	else
	{
		resultColor = color;
	}

	if (useTexture == false)
		FragColor = vec4(resultColor, a);
	else
		FragColor = texture(ourTexture, TexCoord) * vec4(resultColor, a);
}

vec3 CalculateDirLight()
{
	vec3 ambient = directionalLight.ambient;
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-directionalLight.direction);

	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = directionalLight.diffuse * diff;
	vec3 viewDir = normalize(viewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = directionalLight.specular * spec;
	vec3 result = (ambient + diffuse + specular) * color;

	return result;
}