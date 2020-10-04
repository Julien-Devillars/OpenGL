#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 texcoord;

uniform mat4 mvMatrix;
uniform mat4 projMatrix;

out VS_OUT
{
	vec3 position;
	vec3 normal;
	vec2 texcoord;
} vs_out;

void main()
{

    gl_Position = projMatrix * mvMatrix * vec4(position, 1.0f);
	vs_out.texcoord = texcoord.xy;
}