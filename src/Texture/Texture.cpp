#include <GL/glew.h>
#include <string>
#include "stb/stb_image.h"
#include "spdlog/spdlog.h"
#include "Texture.h"
#include "Shader/Shader.h"
#include "Utils/MiscHelper.h"
#include "Error/GLError.h"

 void Texture::flip() {
	stbi_set_flip_vertically_on_load(true);
}

 Texture Texture::from_image(std::string filename, Shader& shaderProgram, const std::string& uniform_id) {
	const std::vector<std::string> spl_res = helper::split(filename, '.');
	if (spl_res.size() != 2)spdlog::error("Invalid filename format: {}", filename);
	std::string extension = spl_res[1];
	if (extension != "png" && extension != "jpg")spdlog::error("Invalid file extension: {}", extension);

	std::string path = helper::format("./Resources/Images/{}", filename);
	const char* path_cstr = path.c_str();

	Texture ret;
	unsigned char* im_data = stbi_load(path_cstr, &ret.width, &ret.height, &ret.nrChannels, 0);

	//Create texture
	glc(glGenTextures(1, &ret.id));

	const unsigned int unit = shaderProgram.getTextureUnit();
	if (unit > 31)spdlog::error("Texture unit cannot be greater than 31");
	ret.type = GL_TEXTURE0 + unit;

	glc(glActiveTexture(ret.type));
	glc(glBindTexture(GL_TEXTURE_2D, ret.id));
	shaderProgram.addTexture(uniform_id);

	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	//Generate texture
	if (im_data) {
		const unsigned int type = extension == "png" ? GL_RGBA : GL_RGB;
		glc(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ret.width, ret.height, 0, type, GL_UNSIGNED_BYTE, im_data));
		glc(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else {
		spdlog::error("Texture not loaded. File: {}", filename);
	}

	stbi_image_free(im_data);

	spdlog::info("Texture successfully loaded from file {}", path);
	ret.defined = true;
	return ret;
}


Texture* Texture::activate() {
	if (type == 0 || !defined)spdlog::error("Texture activated before definition or type set");
	glc(glActiveTexture(type));
	return this;
}

Texture* Texture::bind() {
	if (!defined)spdlog::error("Texture bound before definition");
	glc(glBindTexture(GL_TEXTURE_2D, id));
	return this;
}
