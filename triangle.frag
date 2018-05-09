#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
in vec3 vertexColor;

uniform sampler2D ourTexture;

void main(void)
{
    FragColor = texture(ourTexture,TexCoord) * vec4(vertexColor,1.0f);
}
