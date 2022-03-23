#ifndef SHAPE_H
#define SHAPE_H

#include "Entity2D/entity2D.h"

namespace GL
{
	enum class SHAPE_TYPE
	{
		TRIANGLE,
		QUAD,
		CUBE
	};

	class GRAPHICSENGINE_API Shape : public Entity
	{
	public:
		Shape(Render* render);
		~Shape();

		void Init(SHAPE_TYPE shapeType);
		void Draw();
	};
}

#endif // !SHAPE_H