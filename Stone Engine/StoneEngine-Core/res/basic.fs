#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 lightPos;

in DATA
{
	vec4 position;
	vec4 color;
	vec2 texCoord;
	flat int texID;
} fs_in;

uniform sampler2D textures[16];

void main()
{
    float distance = 1.0f/length(fs_in.position.xy - lightPos) * 0.2;
	vec4 texColor = fs_in.color;
	if (fs_in.texID > 0)
	{
		int texID = fs_in.texID - 1;

		for (int i = 0; i < 16; i++)
			if (texID == i)
				texColor = fs_in.color * texture(textures[i], fs_in.texCoord);
		
	}
	color = texColor * vec4(distance, distance, distance, 1);
}