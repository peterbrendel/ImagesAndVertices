#version 420 core

in vec3 vColor;
in vec2 vTexCoord;

uniform sampler2D fTexture1;
uniform sampler2D fTexture2;

out vec4 FragColor;

void main() {
	FragColor = mix(texture(fTexture1, vTexCoord), texture(fTexture2, vTexCoord), 0.2);
}
