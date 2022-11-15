#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 vertexPos;
in vec3 vertexNormal;

out vec4 fragColor;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main() {
	vec3 normal = normalize(vertexNormal);
	vec3 lightDir = normalize(light.position - vertexPos);
	vec3 viewDir = normalize(viewPos - vertexPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	
	vec3 ambient = light.ambient * material.ambient;

	float d = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * material.diffuse * d;

	float specularStrengh = 0.5;
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * material.specular * spec;
	
	vec3 color = ambient + diffuse + specular;
	fragColor = vec4(color, 1.0);
}