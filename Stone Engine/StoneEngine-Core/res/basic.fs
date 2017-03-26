#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 lightPos;

in DATA
{
	vec4 position;
	vec4 color;
	vec2 texCoord;
	float texID;
} fs_in;

uniform sampler2D textures[16];

void main()
{
    float distance = 1.0f/length(fs_in.position.xy - lightPos) * 0.2;
	vec4 texColor = fs_in.color;
	if (fs_in.texID > 0.0)
	{
		int texID = int(fs_in.texID - 0.5);
		texColor = texture(textures[texID], fs_in.texCoord);
	}
	color = texColor * distance;
}