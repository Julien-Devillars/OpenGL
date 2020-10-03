#version 430

out vec4 color;

in VS_OUT
{
    vec4 color;
} fs_in;

void main()
{
    //color = vec4(1.0f , 0.0f , 0.0f, 1.0f);
    color = fs_in.color;
}