#version 430

layout (location = 0) in vec4 position;

uniform mat4 mvMatrix;
uniform mat4 projMatrix;

uniform float colorValue;

out VS_OUT
{
    vec4 color;
} vs_out;

void main()
{
    gl_Position =  projMatrix * mvMatrix * position;
    vs_out.color = position * colorValue + vec4(0.5f, 0.5f, 0.5f, 0.0f);
}