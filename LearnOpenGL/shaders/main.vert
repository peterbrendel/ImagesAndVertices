#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main() {
	vec4 pos = vec4(aPos, 1.0);

	TexCoord = aTexCoord;
	Normal = normalMatrix * aNormal;
	FragPos = vec3(model * pos);

	gl_Position = projection * view * model * pos;
}
