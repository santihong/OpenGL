#version 330 core

in vec4 settingColor;
in vec2 outTexCoord;

uniform vec4 OutColor;

uniform sampler2D texture0;


out vec4 FragColor;

void main()
{
    //FragColor = settingColor + OutColor;
    FragColor = texture(texture0, outTexCoord) * (OutColor + settingColor);
}
