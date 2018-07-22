#version 330 core

out vec4	pixelColor;

uniform vec4 uColorModel;

void main()
{
	pixelColor = vec4(uColorModel);
	//pixelColor = vec4(1.0, 0.5, 0.0, 1.0);
}