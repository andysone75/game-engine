#ifndef VERTEX_H
#define VERTEX_H

struct Vector3Float {
public:
	float x;
	float y;
	float z;

	Vector3Float() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3Float(glm::vec3 v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}
};

struct Vertex {
public:
	Vector3Float position;
	Vector3Float color;
	Vector3Float normal;

	Vertex(glm::vec3 position, glm::vec3 color, glm::vec3 normal) {
		this->position = Vector3Float(position);
		this->color = Vector3Float(color);
		this->normal = Vector3Float(normal);
	}

	glm::vec3 getPosition() {
		return glm::vec3(position.x, position.y, position.z);
	}
};

struct Triangle {
public:
	unsigned int i0;
	unsigned int i1;
	unsigned int i2;

	Triangle() {
		i0 = 0;
		i1 = 0;
		i2 = 0;
	}

	Triangle(unsigned int i0, unsigned int i1, unsigned int i2) {
		this->i0 = i0;
		this->i1 = i1;
		this->i2 = i2;
	}
};

#endif
