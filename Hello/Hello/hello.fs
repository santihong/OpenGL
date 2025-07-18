#version 330 core

in vec4 SettingColor;

uniform vec4 OutColor;

out vec4 FragColor;

void main()
{
    FragColor = SettingColor + OutColor;
}
