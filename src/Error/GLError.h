#ifndef GLERROR_H
#define GLERROR_H

#include <string>

namespace gle {
	//Macro to wrap all glew calls
	#define glc(x) gle::GLClearError();\
		x;\
		gle::GLLogCall(#x, __FILE__, __LINE__);

	void GLClearError();
	void GLLogCall(const char* function, const char* path, int line);
	void assert_cond(bool cond, std::string message);
}

#endif //GLERROR_H

