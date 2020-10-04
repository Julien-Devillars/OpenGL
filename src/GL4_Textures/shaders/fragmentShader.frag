#version 430

out vec4 color;

// declare interface
in VS_OUT
{
	vec4 color;
} fs_in;

void main()
{
    //color = vec4(0.0, 0.3, 1.0, 1.0);
    color = fs_in.color;
}