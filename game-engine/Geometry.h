#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <map>
#include <array>

namespace geometry {
	using Lookup = std::map<std::pair<unsigned int, unsigned int>, unsigned int>;

	static unsigned int vertexForEdge(Lookup& lookup, std::vector<Vertex>& vertices, unsigned int first, unsigned int second) {
		Lookup::key_type key(first, second);
		if (key.first > key.second)
			std::swap(key.first, key.second);

		auto inserted = lookup.insert({ key, vertices.size() });
		if (inserted.second) {
			Vertex edge0 = vertices[first];
			Vertex edge1 = vertices[second];
			Vertex point = Vertex(glm::normalize(edge0.getPosition() + edge1.getPosition()), glm::vec3(1.0f), glm::vec3(0.0f));
			vertices.push_back(point);
		}

		return inserted.first->second;
	}

	static std::vector<Triangle> subdivide(std::vector<Vertex>& vertices, std::vector<Triangle> tris) {
		Lookup lookup;
		std::vector<Triangle> result;

		for (int i = 0; i < tris.size(); i++) {
			Triangle each = tris[i];
			std::array<unsigned int, 3> mid;
			mid[0] = vertexForEdge(lookup, vertices, each.i0, each.i1);
			mid[1] = vertexForEdge(lookup, vertices, each.i1, each.i2);
			mid[2] = vertexForEdge(lookup, vertices, each.i2, each.i0);
			result.push_back(Triangle(each.i0, mid[0], mid[2]));
			result.push_back(Triangle(each.i1, mid[1], mid[0]));
			result.push_back(Triangle(each.i2, mid[2], mid[1]));
			result.push_back(Triangle(mid[0], mid[1], mid[2]));
		}

		return result;
	}

	static Mesh createIcosphere(int subdivisions) {
		const float x = 0.525731112119133606f;
		const float z = 0.850650808352039932f;
		const float n = 0.0f;

		glm::vec3 verticesPos[] = {
			glm::vec3(-x,  n,  z),
			glm::vec3(x,  n,  z),
			glm::vec3(-x,  n, -z),
			glm::vec3(x,  n, -z),
			glm::vec3(n,  z,  x),
			glm::vec3(n,  z, -x),
			glm::vec3(n, -z,  x),
			glm::vec3(n, -z, -x),
			glm::vec3(z,  x,  n),
			glm::vec3(-z,  x,  n),
			glm::vec3(z, -x,  n),
			glm::vec3(-z, -x,  n),
		};

		unsigned int indices[] = {
			0, 4, 1,
			0, 9, 4,
			9, 5, 4,
			4, 5, 8,
			4, 8, 1,
			8, 10, 1,
			8, 3, 10,
			5, 3, 8,
			5, 2, 3,
			2, 7, 3,
			7, 10, 3,
			7, 6, 10,
			7, 11, 6,
			11, 0, 6,
			0, 1, 6,
			6, 1, 10,
			9, 0, 11,
			9, 11, 2,
			9, 2, 5,
			7, 2, 11,
		};

		int n_indices = sizeof(indices) / sizeof(unsigned int);

		std::vector<Vertex> vertices;
		std::vector<Triangle> tris;

		for (int i = 0; i < n_indices; i += 3)
		{
			unsigned int i0 = indices[i];
			unsigned int i1 = indices[i + 1];
			unsigned int i2 = indices[i + 2];

			Vertex v0 = Vertex(verticesPos[i0], glm::vec3(1.0f), glm::vec3(0.0f));
			Vertex v1 = Vertex(verticesPos[i1], glm::vec3(1.0f), glm::vec3(0.0f));
			Vertex v2 = Vertex(verticesPos[i2], glm::vec3(1.0f), glm::vec3(0.0f));

			vertices.push_back(v0);
			vertices.push_back(v1);
			vertices.push_back(v2);

			tris.push_back(Triangle(i, i + 1, i + 2));
		}

		for (int i = 0; i < subdivisions; i++)
		{
			tris = subdivide(vertices, tris);
		}

		return Mesh(vertices, tris);
	}

	static Mesh createUVSphere(float radius, int slices, int stacks) {
		std::vector<Vertex> vertices;
		std::vector<Triangle> tris;

		float pi = glm::pi<float>();
		float deltaSlice = pi / slices;
		float deltaStack = 2.0f * pi / stacks;

		for (int i = 0; i <= slices; i++)
		{
			float angle = pi / 2.0f - i * deltaSlice;
			float xy = radius * glm::cos(angle);
			float z = radius * glm::sin(angle);

			for (int j = 0; j <= stacks; j++)
			{
				float angle = j * deltaStack;

				glm::vec3 pos = glm::vec3(0.0f);
				pos.x = xy * glm::cos(angle);
				pos.y = xy * glm::sin(angle);
				pos.z = z;
				vertices.push_back(Vertex(pos, glm::vec3(1.0f), glm::vec3(0.0f)));
			}
		}

		unsigned int k1, k2;
		for (int i = 0; i < slices; i++)
		{
			k1 = i * (stacks + 1);
			k2 = k1 + stacks + 1;

			for (int j = 0; j < stacks; j++, k1++, k2++)
			{
				if (i != 0) {
					tris.push_back(Triangle(k1, k2, k1 + 1));
				}

				if (i != (slices - 1)) {
					tris.push_back(Triangle(k1 + 1, k2, k2 + 1));
				}
			}
		}

		return Mesh(vertices, tris);
	}

	static Mesh createCube() {
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
		std::vector<Triangle> tris;

		for (int i = 0; i < n_indices; i += 3)
		{
			unsigned int i0 = cubeIndices[i];
			unsigned int i1 = cubeIndices[i + 1];
			unsigned int i2 = cubeIndices[i + 2];

			vertices.push_back(Vertex(cube[i0], glm::vec3(1.0f), glm::vec3(0.0f)));
			vertices.push_back(Vertex(cube[i1], glm::vec3(1.0f), glm::vec3(0.0f)));
			vertices.push_back(Vertex(cube[i2], glm::vec3(1.0f), glm::vec3(0.0f)));

			tris.push_back(Triangle(i, i + 1, i + 2));
		}

		return Mesh(vertices, tris);
	}
}

#endif
