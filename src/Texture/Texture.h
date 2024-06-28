#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "Shader/Shader.h"

class Texture {
	bool defined = false;
	unsigned int id = -1;
	unsigned int type = 0;
	int width = 0, height = 0, nrChannels = 0;
public:
	static void flip();
	static Texture from_image(std::string filename, Shader& shaderProgram, const std::string& uniform_id);
	Texture* activate();
	Texture* bind();
};

#endif //TEXTURE_H
