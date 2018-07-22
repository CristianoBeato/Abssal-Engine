#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textcoord;

out vec4 varTexCoord;

uniform mat4	uModel;
uniform mat4	uViewProjection;
uniform mat4	uTextureMatrix;

void main()
{
	//gl_Position = uViewProjection * uModel * vec4(position, 1.0);
	gl_Position = vec4(position, 1.0);
	
	varTexCoord = vec4(textcoord.xy, textcoord.xy) * uTextureMatrix;
}