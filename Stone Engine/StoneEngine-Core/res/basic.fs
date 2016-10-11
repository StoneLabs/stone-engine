#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 lightPos;

in vec4 pos;

void main()
{
    float distance = 1.0f/length(pos.xy - lightPos) * 0.2;
    color = colour * distance;
}