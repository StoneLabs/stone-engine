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

		if (texID == 0) texColor = fs_in.color * texture(textures[0], fs_in.texCoord);
		else if (texID == 1) texColor = fs_in.color * texture(textures[1], fs_in.texCoord);
		else if (texID == 2) texColor = fs_in.color * texture(textures[2], fs_in.texCoord);
		else if (texID == 3) texColor = fs_in.color * texture(textures[3], fs_in.texCoord);
		else if (texID == 4) texColor = fs_in.color * texture(textures[4], fs_in.texCoord);
		else if (texID == 5) texColor = fs_in.color * texture(textures[5], fs_in.texCoord);
		else if (texID == 6) texColor = fs_in.color * texture(textures[6], fs_in.texCoord);
		else if (texID == 7) texColor = fs_in.color * texture(textures[7], fs_in.texCoord);
		else if (texID == 8) texColor = fs_in.color * texture(textures[8], fs_in.texCoord);
		else if (texID == 9) texColor = fs_in.color * texture(textures[9], fs_in.texCoord);
		else if (texID == 10) texColor = fs_in.color * texture(textures[10], fs_in.texCoord);
		else if (texID == 11) texColor = fs_in.color * texture(textures[11], fs_in.texCoord);
		else if (texID == 12) texColor = fs_in.color * texture(textures[12], fs_in.texCoord);
		else if (texID == 13) texColor = fs_in.color * texture(textures[13], fs_in.texCoord);
		else if (texID == 14) texColor = fs_in.color * texture(textures[14], fs_in.texCoord);
		else if (texID == 15) texColor = fs_in.color * texture(textures[15], fs_in.texCoord);

		
	}
	color = texColor * vec4(distance, distance, distance, 1);
}