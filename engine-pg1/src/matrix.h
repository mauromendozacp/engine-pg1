#ifndef MATRIX_H
#define MATRIX_H

#include "GLM/glm.hpp"

namespace GL
{
	struct Matrix
	{
		glm::mat4 model;
		glm::mat4 translate;
		glm::mat4 rotation;
		glm::mat4 scale;
	};
}

#endif // !MATRIX_H