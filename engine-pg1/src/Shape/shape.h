#ifndef SHAPE_H
#define SHAPE_H

#include "Entity2D/entity2D.h"

namespace GL
{
	enum SHAPE_TYPE
	{
		TRIANGLE
	};

	class GRAPHICSENGINE_API Shape : public Entity2D
	{
	public:
		Shape(Render* render, SHAPE_TYPE shapeType);
		~Shape();

		void Init();
		void Draw();

	private:
		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;

		float* vertices;
		unsigned int* indices;

		SHAPE_TYPE shapeType;
	};
}

#endif // !SHAPE_H