#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <unordered_map>
#include <string>

#include "glm/glm.hpp"

class Shader {
	unsigned int id = -1, textureUnit = 0;
	std::string m = "", v = "", p = "", n = "";
	std::string specular, shininess;
	std::string lambient, lspecular, ldiffuse;
	bool mat_uni_def = false;
	bool light_uni_def = false;
	bool mvpn_def = false;
	std::unordered_map<std::string, int> uniform_cache;

	static std::string get_source(const std::string& filename);

public:
	Shader() = default;

	unsigned int getTextureUnit() const;
	void addTexture(const std::string& uniform);
	static Shader parse(std::string vertex_path, std::string fragment_path);
	void attach() const;
	static void deattach();
	void cache_uniform(std::string uniform_id);
	void uniform4f(const std::string& uniform_id, float f1, float f2, float f3, float f4);
	void uniform3f(const std::string& uniform_id, float f1, float f2, float f3);
	void uniform1i(const std::string& uniform_id, int i);
	void uniform1f(const std::string& uniform_id, float i);
	void uniformMatrix4f(const std::string& uniform_id, glm::mat4 mat);
	void uniformMatrix3f(const std::string& uniform_id, glm::mat3 mat);
	void model(const glm::mat4& model_mat, bool normal_mat);
	void view(const glm::mat4& view_mat);
	void project(const glm::mat4& project_mat);
	void set_mvpn(const std::string& m, const std::string &v, const std::string& p, const std::string &n);
	void set_mat_uniforms(const std::string &spec, const std::string &shi);
	void set_material(float shi);
	void set_light_uniforms(const std::string& amb, const std::string &spec, const std::string &diff);
	void set_light(glm::vec3 amb, glm::vec3 spec, glm::vec3 diff, float constant, float linear, float quadratic);
};

#endif //SHADER_H
