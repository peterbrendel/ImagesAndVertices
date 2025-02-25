#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;
uniform vec3 lightPos;

void main() {
	vec4 pos = vec4(aPos, 1.0);

	TexCoord = aTexCoord;
	Normal = normalMatrix * aNormal;
	FragPos = vec3(view * model * pos);
	LightPos = vec3(view * vec4(lightPos, 1.0));

	gl_Position = projection * view * model * pos;
}
