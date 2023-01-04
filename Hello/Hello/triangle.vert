#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertexColor;
out vec2 texCoord;

void main()
{
    gl_Position = projection * view * model * vec4(aPos.xyz, 1.0);
    vertexColor = vec4(aColor.xyz, 1.0);
    texCoord = aTexCoord;
}
