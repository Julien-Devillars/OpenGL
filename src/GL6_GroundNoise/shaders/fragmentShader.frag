#version 430

out vec4 color;

in VS_OUT
{
	vec3 position;
	vec3 normal;
	vec2 texcoord;
} fs_in;

layout(binding = 0) uniform sampler2D myTexture;

void main()
{
	color = vec4(texture(myTexture, fs_in.texcoord).xyz, 1.0f);
}