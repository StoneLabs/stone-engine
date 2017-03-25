#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 lightPos;
uniform sampler2D tex;

in DATA
{
	vec4 position;
	vec4 color;
	vec2 texCoord;
} fs_in;

void main()
{
    float distance = 1.0f/length(fs_in.position.xy - lightPos) * 0.2;
    color = fs_in.color * distance;
	color = texture(tex, fs_in.texCoord) * distance;
}