#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture {
public:
	unsigned char* data;
	int width, height;
	int channelsCount;
	std::string type;

	void free();
};

void Texture::free() {
	stbi_image_free(data);
}

#endif