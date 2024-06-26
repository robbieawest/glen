#include "GLError.h"

#include "GL/glew.h"
#include "spdlog/spdlog.h"

void gle::GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

void gle::GLLogCall(const char* function, const char* file, int line) {
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {
		spdlog::error("Line {} {}\n| OpenGL ERROR | : [{}] {}", line, file, error, function);
	}
}

void gle::assert_cond(bool cond, std::string message) {
	if (!cond)
		spdlog::error("Assertion error |{}| -> cond was false", message);

}
