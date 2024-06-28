#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <utility>
#include <string>

#include "spdlog/spdlog.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.h"
#include "MiscHelper.h"
#include "GLError.h"
#include "GlenConstants.h"

std::string Shader::get_source(const std::string& filename) {
	std::string path = helper::format(resourcesPath + shadersPath + filenameInput, filename);

	std::ifstream parser(path);
	if (!parser.is_open())
		spdlog::error("shader does not exist at path: {}", path);

	std::string ret, line;
	while (std::getline(parser, line))
		ret += line + '\n';

	parser.close();
	return ret;
}

unsigned int Shader::getTextureUnit() const {
	return textureUnit;
}

void Shader::addTexture(const std::string& uniform) {
	attach();
	uniform1i(uniform, textureUnit++);
}


 Shader Shader::parse(std::string vertex_path, std::string fragment_path) {

	//Parse paths and get sources
	std::string vertex_source = get_source(vertex_path);
	const char* vertex_input = vertex_source.c_str();
	std::string fragment_source = get_source(fragment_path);
	const char* fragment_input = fragment_source.c_str();

	//Create vertex shader
	glc(unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER));
	glc(glShaderSource(vertex_shader, 1, &vertex_input, nullptr));
	glc(glCompileShader(vertex_shader));

	//Check vertex shader compilation
	int success;
	char infolog[512];
	glc(glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success));
	if (!success) {
		glc(glGetShaderInfoLog(vertex_shader, 512, nullptr, infolog));
		spdlog::error("|VERTEX SHADER COMPILATION ERROR|\n{}", infolog);
	}


	//Create fragment shader
	glc(unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER));
	glc(glShaderSource(fragment_shader, 1, &fragment_input, nullptr));
	glc(glCompileShader(fragment_shader));

	//Check fragment shader compilation
	glc(glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success));
	if (!success) {
		glc(glGetShaderInfoLog(fragment_shader, 512, nullptr, infolog));
		spdlog::error("|FRAGMENT SHADER COMPILATION ERROR|\n{}", infolog);
	}

	Shader ret;

	//Create shader program
	glc(ret.id = glCreateProgram());
	glc(glAttachShader(ret.id, vertex_shader));
	glc(glAttachShader(ret.id, fragment_shader));
	glc(glLinkProgram(ret.id));

	//Check shader linking
	glc(glGetProgramiv(ret.id, GL_LINK_STATUS, &success));
	if (!success) {
		glc(glGetProgramInfoLog(ret.id, 512, nullptr, infolog));
		spdlog::error("|SHADER PROGRAM LINKING ERROR|\n{}", infolog);
	}

	ret.attach();
	glc(glDeleteShader(fragment_shader));
	glc(glDeleteShader(vertex_shader));

	spdlog::info("Shader parsed without error from {} and {}", vertex_path, fragment_path);

	return ret;
}

void Shader::attach() const {
	glc(glUseProgram(id));
}

void Shader::deattach() {
	glc(glUseProgram(0));
}

void Shader::cache_uniform(std::string uniform_id) {
	if (uniform_cache.contains(uniform_id)) {
		//Not cached
		const char* uniform_id_cstr = uniform_id.c_str();
		glc(int uniform_location = glGetUniformLocation(id, uniform_id_cstr));
		if (uniform_location == -1) {
			spdlog::warn("uniform '{}' is not associated with shader", uniform_id);
			return;
		}

		uniform_cache.insert({ uniform_id, uniform_location });
	}
}


void Shader::uniform4f(const std::string& uniform_id, float f1, float f2, float f3, float f4) {
	cache_uniform(uniform_id);

	glc(glUniform4f(uniform_cache[uniform_id], f1, f2, f3, f4));
}

void Shader::uniform3f(const std::string& uniform_id, float f1, float f2, float f3) {
	cache_uniform(uniform_id);

	glc(glUniform3f(uniform_cache[uniform_id], f1, f2, f3));
}

void Shader::uniform1i(const std::string& uniform_id, int i) {
	cache_uniform(uniform_id);

	glc(glUniform1i(uniform_cache[uniform_id], i));
}

void Shader::uniform1f(const std::string& uniform_id, float i) {
	cache_uniform(uniform_id);

	glc(glUniform1f(uniform_cache[uniform_id], i));
}

void Shader::uniformMatrix4f(const std::string& uniform_id, glm::mat4 mat) {
	cache_uniform(uniform_id);

	glc(glUniformMatrix4fv(uniform_cache[uniform_id], 1, false, glm::value_ptr(mat)));
}

void Shader::uniformMatrix3f(const std::string& uniform_id, glm::mat3 mat) {
	cache_uniform(uniform_id);

	glc(glUniformMatrix3fv(uniform_cache[uniform_id], 1, false, glm::value_ptr(mat)));
}

void Shader::model(const glm::mat4& model_mat, const bool normal_mat) {
	if (!mvpn_def) {
		spdlog::warn("mvpn not set for model");
		return;
	}
	uniformMatrix4f(m, model_mat);
	if (normal_mat) {
		if (n == "")
			spdlog::warn("normal matrix attempted to be changed when n is not set");
		else
			uniformMatrix3f(n, glm::mat3(glm::transpose(glm::inverse(model_mat))));
	}
}

void Shader::view(const glm::mat4& view_mat) {
	if (!mvpn_def) {
		spdlog::warn("mvpn not set for model");
		return;
	}
	uniformMatrix4f(v, view_mat);
}

void Shader::project(const glm::mat4& project_mat) {
	if (!mvpn_def) {
		spdlog::warn("mvpn not set for model");
		return;
	}
	uniformMatrix4f(p, project_mat);
}

void Shader::set_mvpn(const std::string& m, const std::string &v, const std::string& p, const std::string &n) {
	mvpn_def = true;
	cache_uniform(m);
	cache_uniform(v);
	cache_uniform(p);
	this->m = m;
	this->v = v;
	this->p = p;

	if (n == "")return;
	cache_uniform(n);
	this->n = n;
}

void Shader::set_mat_uniforms(const std::string &spec, const std::string &shi) {
	mat_uni_def = true;
	cache_uniform(spec);
	cache_uniform(shi);

	specular = spec;
	shininess = shi;
}

void Shader::set_material(const float shi) {
	if (!mat_uni_def) {
		spdlog::warn("material uniforms have not been defined.");
		return;
	}

	uniform1f(shininess, shi);
}

void Shader::set_light_uniforms(const std::string& amb, const std::string &spec, const std::string &diff) {
	light_uni_def = true;
	cache_uniform(amb);
	cache_uniform(spec);
	cache_uniform(diff);

	lambient = amb;
	lspecular = spec;
	ldiffuse = diff;
}

void Shader::set_light(const glm::vec3 amb, const glm::vec3 spec, const glm::vec3 diff, const float constant,
                       const float linear, const float quadratic) {
	if (!light_uni_def) {
		spdlog::warn("light uniforms have not been defined.");
		return;
	}

	uniform3f(lambient, amb.x, amb.y, amb.z);
	uniform3f(lspecular, spec.x, spec.y, spec.z);
	uniform3f(ldiffuse, diff.x, diff.y, diff.z);
	uniform1f("light.constant", constant);
	uniform1f("light.linear", linear);
	uniform1f("light.quadratic", quadratic);
}

