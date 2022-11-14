#version 330 core

in vec3 vertexPos;
in vec3 vertexColor;
in vec3 vertexNormal;

out vec4 fragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main() {
	vec3 normal = normalize(vertexNormal);
	vec3 lightDir = normalize(lightPos - vertexPos);
	vec3 viewDir = normalize(viewPos - vertexPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	float d = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = lightColor * d;

	float specularStrengh = 0.5;
	float specular = pow(max(dot(viewDir, reflectDir), 0.0), 8);
	
	vec3 color = vertexColor * (ambient + diffuse + specular);
	fragColor = vec4(color, 1.0);
}