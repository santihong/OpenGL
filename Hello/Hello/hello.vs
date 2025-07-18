#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 SettingColor;

void main()
{
	gl_Position = vec4(aPos.xyz, 1.0);

	SettingColor = aColor;
}
