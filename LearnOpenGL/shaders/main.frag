#version 420 core

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;

uniform sampler2D fTexture1;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

out vec4 FragColor;

void main() {
	vec3 norm = normalize(Normal);

	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;


	vec3 light = (lightColor * 0.1 + diffuse + specular) * objectColor;
	FragColor = vec4(light, 1.0) * texture(fTexture1, TexCoord);
}
