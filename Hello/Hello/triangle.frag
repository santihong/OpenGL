#version 330 core

in vec4 vertexColor;
in vec2 texCoord;

out vec4 FragColor;

uniform vec4 tilingColor;
uniform sampler2D aTexture;

void main() {
	FragColor = texture(aTexture, texCoord) * vertexColor;
	FragColor = vec4(FragColor.r, FragColor.g * tilingColor.g, FragColor.ba);
