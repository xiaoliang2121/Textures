#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aColor;
out vec2 TexCoord;
out vec3 vertexColor;

uniform mat4 transform;

void main(void)
{
    gl_Position = transform * vec4(aPos, 1.0f);
    TexCoord = aTexCoord;
    vertexColor = aColor;
}
