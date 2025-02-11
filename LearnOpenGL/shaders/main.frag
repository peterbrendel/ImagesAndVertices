#version 420 core

in vec2 texCoord;

uniform sampler2D fTexture1;

out vec4 FragColor;

void main() {
	FragColor = texture(fTexture1, texCoord);
}
