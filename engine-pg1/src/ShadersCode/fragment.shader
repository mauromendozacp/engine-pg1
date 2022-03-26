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

struct SpotLight {
	PointLight pointLight;
	vec3 direction;
	float cutOff;
	bool enabled;
};

uniform vec3 color;
uniform float a;

uniform Light baselight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

uniform sampler2D ourTexture;
uniform bool useTexture;
uniform bool affectedLight;
uniform vec3 viewPosition;

vec3 CalculateDirLight();
vec3 CalculatePointLight(PointLight pLight);
vec3 CalculateSpotLight();

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
			resultColor += CalculatePointLight(pointLight);
		}
		if (spotLight.enabled == true)
		{
			resultColor += CalculateSpotLight();
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

vec3 CalculatePointLight(PointLight pLight) {
	vec3 lightDir = pLight.position - FragPos;
	float distance = length(lightDir);
	lightDir = normalize(lightDir);

	vec3 ambient = pLight.ambient;
	vec3 norm = normalize(Normal);

	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = pLight.diffuse * diff;
	vec3 viewDir = normalize(viewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = pLight.specular * spec;

	float attenuation = pLight.quadratic * distance * distance + pLight.linear * distance + pLight.constant;

	vec3 result = ((ambient + diffuse + specular) / attenuation) * pLight.color;
	return result;
}

vec3 CalculateSpotLight()
{
	vec3 lightDir = normalize(spotLight.pointLight.position - FragPos);
	float factor = dot(lightDir, normalize(-spotLight.direction));

	vec3 res = CalculatePointLight(spotLight.pointLight) * (1.0f - (1.0f - factor) * (1.0f / (1.0f - spotLight.cutOff)));
	return res;
}