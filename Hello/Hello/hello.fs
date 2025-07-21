#version 330 core

in vec4 settingColor;
in vec2 outTexCoord;

uniform vec4 OutColor;

uniform sampler2D texture1;
uniform sampler2D texture2;


out vec4 FragColor;

void main()
{
    //FragColor = settingColor + OutColor;
    FragColor = (texture(texture1, outTexCoord) * 0.3 + texture(texture2, outTexCoord) * 0.7 * (OutColor + settingColor));
}
