#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 vertexPos;
in vec3 vertexColor;
in vec3 vertexNormal;

out vec4 fragColor;

uniform Material material;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main() {
	vec3 normal = normalize(vertexNormal);
	vec3 lightDir = normalize(lightPos - vertexPos);
	vec3 viewDir = normalize(viewPos - vertexPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor * material.ambient;

	float d = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = lightColor * material.diffuse * d;

	float specularStrengh = 0.5;
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = lightColor * material.specular * spec;
	
	vec3 color = ambient + diffuse + specular;
	fragColor = vec4(color, 1.0);
}