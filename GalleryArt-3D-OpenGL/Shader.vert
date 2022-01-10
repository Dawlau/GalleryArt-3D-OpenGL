#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
layout(location=2) in vec3 in_Normal;

out vec3 FragPos;
out vec3 Normal;
out vec3 inLightPos;
out vec3 inViewPos;


uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {

	gl_Position = projectionMatrix * viewMatrix * in_Position;

    FragPos = vec3(gl_Position);
    Normal = vec3(projectionMatrix * viewMatrix * vec4(in_Normal, 0.0));
    inLightPos = vec3(projectionMatrix * viewMatrix * vec4(lightPos, 1.0f));
    inViewPos = vec3(projectionMatrix * viewMatrix * vec4(viewPos, 1.0f));
}