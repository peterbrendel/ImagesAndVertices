#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform vec3 uTranslation;
uniform vec3 uScaling;

out vec2 vTexCoord;

void main() {
	gl_Position = vec4((aPos + uTranslation) * uScaling, 1.0);
	vTexCoord = aTexCoord;
}
