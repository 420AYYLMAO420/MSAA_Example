#version 430 core

out vec4 gl_Color;
uniform vec4 uColor;

void main()
{
    gl_Color = uColor;
}