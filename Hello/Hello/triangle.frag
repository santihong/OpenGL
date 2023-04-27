#version 330 core

//in vec2 texCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D aTex1;
uniform sampler2D aTex2;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambient;
uniform float specular;
uniform float specularPow;

out vec4 FragColor;

void main() {
	//FragColor = mix(texture(aTex1, texCoord), texture(aTex2, texCoord), 0.2);
	vec3 ambientColor = ambient * lightColor;
	
	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuse = max(dot(norm, lightDir), 0.0);
	vec3 diffuseColor = diffuse * lightColor;

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, Normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), specularPow);
	vec3 specularColor = specular * spec * lightColor;

	vec3 color = ambientColor + diffuseColor + specularColor;
	FragColor = vec4(color * objectColor, 1.0);
}