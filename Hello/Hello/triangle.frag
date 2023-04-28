#version 330 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform Material material;

out vec4 FragColor;

void main() {
	vec3 ambientColor = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diffuse = max(dot(norm, lightDir), 0.0);
	vec3 diffuseColor = light.diffuse * diffuse * vec3(texture(material.diffuse, TexCoords));

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, Normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);
	vec3 specularColor = light.specular * spec * vec3(texture(material.specular, TexCoords));

	vec3 color = ambientColor + diffuseColor + specularColor;
	FragColor = vec4(color, 1.0);
}
