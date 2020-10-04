#version 430

layout (location = 0) in vec4 position;

uniform mat4 mvMatrix;
uniform mat4 projMatrix;

// declare interface
out VS_OUT
{
	vec4 color;
} vs_out;

void main()
{

    gl_Position = projMatrix * mvMatrix * position;
	vs_out.color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}