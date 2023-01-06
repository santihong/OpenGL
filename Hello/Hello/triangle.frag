#version 330 core

in vec4 vertexColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D aTex1;
uniform sampler2D aTex2;

void main() {
	// FragColor = mix(texture(aTex1, texCoord), texture(aTex2, texCoord), 0.2) * vertexColor;
	FragColor = mix(texture(aTex1, texCoord), texture(aTex2, texCoord), 0.2);
}