#version 430 core

in vec2 Position2D; 

void main() {
	//leave position unchanged
	gl_Position = vec4(Position2D.x, Position2D.y, 0, 1);
}