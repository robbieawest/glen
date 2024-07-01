#include "GL/glew.h"
#include "GLError.h"
#include "Utils/MiscHelper.h"
#include "Utils/LogType.h"

void gle::GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

void gle::GLLogCall(const char* function, const char* path, int line) {
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {
		const std::string file = helper::split(path, '/').back();
		helper::log(LogType::ERROR, "|OpenGL Error {}| : {}", {std::to_string(error), function});
	}
}

void gle::assert_cond(bool cond, std::string message) {
	if (!cond)
		helper::log(LogType::ERROR, __func__, "Assertion error |{}| -> cond was false", {message});
}
