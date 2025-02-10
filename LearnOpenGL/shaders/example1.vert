#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 vColor;
out vec2 vTexCoord;

void main() {
	gl_Position = vec4(aPos.x, aPos.y*-1, aPos.z, 1.0);
	vColor = aColor;
	vTexCoord = aTexCoord;
}
