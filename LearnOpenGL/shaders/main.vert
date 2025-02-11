#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform vec3 translation;
uniform vec3 scaling;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;

void main() {
	vec4 pos = vec4((aPos + translation) * scaling, 1.0);
	gl_Position = projection * view * model * pos;
	texCoord = aTexCoord;
}
