#ifndef SHAPE_H
#define SHAPE_H

#include "Entity/Entity2D/entity2D.h"

namespace GL
{
	enum class SHAPE_TYPE
	{
		TRIANGLE,
		QUAD,
		CUBE
	};

	class GRAPHICSENGINE_API Shape : public Entity2D
	{
	public:
		Shape();
		Shape(Render* render);
		~Shape();

		void Init(SHAPE_TYPE shapeType);
		void Draw();
		void DeInit();
	};
}

#endif // !SHAPE_H