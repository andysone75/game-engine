#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;

	sampler2D diffuseTexture;
	sampler2D normalTexture;
};

struct Light {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in VS_OUT {
	vec3 fragPos;
	vec3 fragNormal;
	vec2 fragUv;
	vec3 tangentLightPos;
	vec3 tangentViewPos;
	vec3 tangentFragPos;
} fs_in;

out vec4 fragColor;

uniform Material material;
uniform Light light;

void main() {
//	vec3 normal = fs_in.fragNormal;
	vec3 normal = texture(material.normalTexture, fs_in.fragUv).rgb;
	normal = normal * 2.0 - 1.0;

	vec3 lightDir = normalize(fs_in.tangentLightPos - fs_in.tangentFragPos);
	vec3 viewDir = normalize(fs_in.tangentViewPos - fs_in.tangentFragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	
	vec3 ambient = light.ambient * material.ambient;

	float d = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * material.diffuse * d;

	float specularStrengh = 0.5;
	float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
	vec3 specular = light.specular * material.specular * spec;
	
	vec4 diffuseColor = texture(material.diffuseTexture, fs_in.fragUv);
	vec3 color = diffuseColor.rgb * (ambient + diffuse + specular);
	fragColor = vec4(color, 1.0);

//	fragColor = texture(material.diffuseTexture, fs_in.fragUv);	
//	fragColor = texture(material.normalTexture, fs_in.fragUv);

//	fragColor = vec4(normal, 1.0);
}