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

struct PointLight
{
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

struct SpotLight
{
	PointLight pointLight;
	vec3 direction;
	float cutOff;
	bool enabled;
};

struct Material
{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform vec3 color;
uniform float a;

uniform Light baselight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

uniform sampler2D ourTexture;
uniform bool useTexture;
uniform bool useMaterial;
uniform bool affectedLight;
uniform Material material;
uniform vec3 viewPosition;

vec3 CalculateDirLight(Material m, vec3 norm, vec3 viewDir);
vec3 CalculatePointLight(PointLight pLight, Material m, vec3 norm, vec3 fragPos, vec3 viewDir);
vec3 CalculateSpotLight(SpotLight sLight, Material m, vec3 norm, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 resultColor = vec3(0.0f, 0.0f, 0.0f);
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPosition - FragPos);
	Material mat;

	if (useMaterial)
	{
		mat = material;
	}
	else
	{
		mat.shininess = 1.0f;
		mat.ambient = vec3(1.0f, 1.0f, 1.0f);
		mat.diffuse = vec3(1.0f, 1.0f, 1.0f);
		mat.specular = vec3(1.0f, 1.0f, 1.0f);
	}

	if (affectedLight == true)
	{
		/*if (baselight.enabled == true)
		{
			resultColor = material.ambient * baselight.color;
		}*/
		if (directionalLight.enabled == true)
		{
			resultColor += CalculateDirLight(mat, norm, viewDir);
		}
		if (pointLight.enabled == true)
		{
			resultColor += CalculatePointLight(pointLight, mat, norm, Fragpos, viewDir);
		}
		if (spotLight.enabled == true)
		{
			resultColor += CalculateSpotLight(spotLight, mat, norm, Fragpos, viewDir);
		}
	}
	else
	{
		resultColor = color;
	}

	if (useTexture == false)
	{
		FragColor = vec4(resultColor, a);
	}
	else
	{
		FragColor = texture(ourTexture, TexCoord) * vec4(resultColor, a);
	}
}

vec3 CalculateDirLight(Material m, vec3 norm, vec3 viewDir)
{
	vec3 lightDir = normalize(-directionalLight.direction);
	float diff = max(dot(norm, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), m.shininess);

	vec3 ambient = directionalLight.ambient * vec3(texture(m.diffuse, TexCoord));
	vec3 diffuse = directionalLight.diffuse * diff * vec3(texture(m.diffuse, TexCoord));
	vec3 specular = directionalLight.specular * spec * vec3(texture(m.specular, TexCoord));

	vec3 result = (ambient + diffuse + specular);
	return result;
}

vec3 CalculatePointLight(PointLight pLight, Material m, vec3 norm, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = pLight.position - fragPos;
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), m.shininess);
	float distance = length(pLight.position - fragPos);
	float attenuation = 1.0 / (pLight.constant + pLight.linear * distance + pLight.quadratic * (distance * distance));

	vec3 ambient = pLight.ambient * vec3(texture(m.diffuse, TexCoord));
	vec3 diffuse = pLight.diffuse * diff * vec3(texture(m.diffuse, TexCoord));
	vec3 specular = pLight.specular * spec * vec3(texture(m.specular, TexCoord));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = (ambient + diffuse + specular);
	return result;
}

vec3 CalculateSpotLight(SpotLight sLight, Material m, vec3 norm, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(sLight.position - fragPos);

	float diff = max(dot(norm, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), m.shininess);

	float distance = length(sLight.position - fragPos);
	float attenuation = 1.0f / (sLight.constant + sLight.linear * distance + sLight.quadratic * (distance * distance));
	
	float theta = dot(lightDir, normalize(-sLight.direction));
	float epsilon = sLight.cutOff - sLight.outerCutOff;
	float intensity = clamp((theta - sLight.outerCutOff) / epsilon, 0.0f, 1.0f);
	
	vec3 ambient = sLight.ambient * vec3(texture(m.diffuse, TexCoord));
	vec3 diffuse = sLight.diffuse * diff * vec3(texture(m.diffuse, TexCoord));
	vec3 specular = sLight.specular * spec * vec3(texture(m.specular, TexCoord));
	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	vec3 result = (ambient + diffuse + specular);
	return result;
}