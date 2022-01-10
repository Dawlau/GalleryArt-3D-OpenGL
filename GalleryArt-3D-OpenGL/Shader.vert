#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
layout(location=2) in vec3 in_Normal;

out vec4 ex_Color;
uniform mat4 normMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {

	gl_Position = projectionMatrix * viewMatrix * normMatrix * in_Position;
	// gl_Position = projectionMatrix * normMatrix * in_Position;
	// gl_Position = viewMatrix * normMatrix * in_Position;
	// gl_Position = normMatrix * in_Position;
  	ex_Color = in_Color;
}