#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 tangent;

out VS_OUT {
	vec3 fragPos;
	vec3 fragNormal;
	vec2 fragUv;
	vec3 tangentLightPos;
	vec3 tangentViewPos;
	vec3 tangentFragPos;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
	vec4 wPos = model * vec4(pos, 1.0);
	mat3 normalMatrix = mat3(transpose(inverse(model)));

	vs_out.fragPos = wPos.xyz;
	vs_out.fragNormal = normalize(normalMatrix * normal);

	vec3 T = normalize(normalMatrix * tangent);
	vec3 B = normalize(cross(vs_out.fragNormal, T));
	mat3 TBN = transpose(mat3(T, B, vs_out.fragNormal));

	vs_out.fragUv = uv;
	vs_out.tangentLightPos = TBN * lightPos;
	vs_out.tangentViewPos = TBN * viewPos;
	vs_out.tangentFragPos = TBN * vs_out.fragPos;

	gl_Position = projection * view * wPos;
}