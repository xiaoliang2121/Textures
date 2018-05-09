#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
in vec3 vertexColor;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main(void)
{
    FragColor = mix(texture(ourTexture1,TexCoord), texture(ourTexture2,vec2(1.0-TexCoord.x,TexCoord.y)),0.2);
}
