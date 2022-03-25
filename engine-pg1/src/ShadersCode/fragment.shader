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

uniform Light baselight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;

uniform sampler2D ourTexture;
uniform bool useTexture;
uniform bool affectedLight;
uniform vec3 viewPosition;

vec3 CalculateDirLight();
vec3 CalculatePointLight();

void main()
{
	vec3 resultColor = color;
	if (affectedLight == true)
	{
		if (baselight.enabled == true)
		{
			resultColor *= baselight.color;
		}
		if (directionalLight.enabled == true)
		{
			resultColor += CalculateDirLight();
		}
		if (pointLight.enabled == true)
		{
			resultColor += CalculatePointLight();
		}
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

vec3 CalculatePointLight() {
	vec3 lightDir = pointLight.position - FragPos;
	float distance = length(lightDir);
	lightDir = normalize(lightDir);

	vec3 ambient = pointLight.ambient;
	vec3 norm = normalize(Normal);

	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = pointLight.diffuse * diff;
	vec3 viewDir = normalize(viewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = pointLight.specular * spec;

	float attenuation = pointLight.quadratic * distance * distance + pointLight.linear * distance + pointLight.constant;

	vec3 result = ((ambient + diffuse + specular) / attenuation) * pointLight.color;
	return result;
}