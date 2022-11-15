#ifndef GEOMETRY_H
#define GEOMETRY_H

namespace geometry {
	static void GeneratePolyNormals(std::vector<Vertex>& vertices, std::vector<Triangle>& tris) {
		std::vector<Vertex> newVertices;
		std::vector<Triangle> newTris;
		for (int i = 0; i < tris.size(); i++)
		{
			Vertex a = vertices[tris[i].i0];
			Vertex b = vertices[tris[i].i1];
			Vertex c = vertices[tris[i].i2];

			glm::vec3 ab = b.position - a.position;
			glm::vec3 ac = c.position - a.position;
			glm::vec3 n = glm::normalize(glm::cross(ac, ab));

			a.normal = n;
			b.normal = n;
			c.normal = n;

			newVertices.push_back(a);
			newVertices.push_back(b);
			newVertices.push_back(c);

			newTris.push_back(Triangle(i * 3 + 0, i * 3 + 1, i * 3 + 2));
		}
		vertices = newVertices;
		tris = newTris;
	}

	static void GenerateNormals(std::vector<Vertex>& vertices, std::vector<Triangle> tris) {
		std::vector<std::vector<glm::vec3>> vertexNormals = std::vector<std::vector<glm::vec3>>(vertices.size());

		for (int i = 0; i < tris.size(); i++)
		{
			Vertex a = vertices[tris[i].i0];
			Vertex b = vertices[tris[i].i1];
			Vertex c = vertices[tris[i].i2];

			glm::vec3 ab = b.position - a.position;
			glm::vec3 ac = c.position - a.position;
			glm::vec3 n = glm::cross(ac, ab);

			vertexNormals[tris[i].i0].push_back(n);
			vertexNormals[tris[i].i1].push_back(n);
			vertexNormals[tris[i].i2].push_back(n);
		}

		for (int i = 0; i < vertices.size(); i++)
		{
			glm::vec3 normal = glm::vec3(0.0f);
			for (int j = 0; j < vertexNormals[i].size(); j++) {
				normal += vertexNormals[i][j];
			}
			normal = glm::normalize(normal);
			vertices[i].normal = normal;
		}
	}

	static Mesh* createCube() {
		glm::vec3 cube[] = {
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f,  0.5f, -0.5f),
			glm::vec3(-0.5f,  0.5f, -0.5f),

			glm::vec3(-0.5f, -0.5f,  0.5f),
			glm::vec3(0.5f, -0.5f,  0.5f),
			glm::vec3(0.5f,  0.5f,  0.5f),
			glm::vec3(-0.5f,  0.5f,  0.5f),
		};

		unsigned int cubeIndices[] = {
			0, 1, 2,
			2, 3, 0,

			0, 3, 7,
			4, 0, 7,

			4, 7, 6,
			5, 4, 6,

			2, 1, 6,
			5, 6, 1,

			3, 2, 7,
			6, 7, 2,

			1, 0, 4,
			5, 1, 4
		};

		int n_indices = sizeof(cubeIndices) / sizeof(unsigned int);

		std::vector<Vertex> vertices;
		std::vector<Triangle> triangles;

		for (int i = 0; i < n_indices; i += 3)
		{
			unsigned int i0 = cubeIndices[i];
			unsigned int i1 = cubeIndices[i + 1];
			unsigned int i2 = cubeIndices[i + 2];

			vertices.push_back(Vertex(cube[i0]));
			vertices.push_back(Vertex(cube[i1]));
			vertices.push_back(Vertex(cube[i2]));

			triangles.push_back(Triangle(i, i + 1, i + 2));
		}

		GeneratePolyNormals(vertices, triangles);

		return new Mesh(vertices, triangles);
	}
}

#endif
