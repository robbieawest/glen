#include "GL/glew.h"
#include "spdlog/spdlog.h"
#include "GLError.h"
#include "Utils/MiscHelper.h"

void gle::GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

void gle::GLLogCall(const char* function, const char* path, int line) {
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {
		const std::string file = helper::split(path, '/').back();
		spdlog::error(
			"OpenGL Error occurred at function call\n\t"
				"| FILE | : {}\n\t"
				"| LINE | : {}\n\t"
				"| Error Description | : [{}] {}"
				, file, line, error, function
				);
	}
}

void gle::assert_cond(bool cond, std::string message) {
	if (!cond)
		spdlog::error("Assertion error |{}| -> cond was false", message);

}
