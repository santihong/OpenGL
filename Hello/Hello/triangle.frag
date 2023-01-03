#version 330 core

in vec4 vertexColor;
in vec2 texCoord;

out vec4 FragColor;

uniform vec4 tilingColor;
uniform sampler2D aTex1;
uniform sampler2D aTex2;

void main() {
	FragColor = mix(texture(aTex1, texCoord), texture(aTex2, texCoord), tilingColor.g) * vertexColor;
	// FragColor = vec4(FragColor.r, FragColor.g * tilingColor.g, FragColor.ba);
}