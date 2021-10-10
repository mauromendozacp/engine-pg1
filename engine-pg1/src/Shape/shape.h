#ifndef SHAPE_H
#define SHAPE_H

#include "Entity2D/entity2D.h"

namespace GL
{
	enum class SHAPE_TYPE
	{
		TRIANGLE
	};

	class GRAPHICSENGINE_API Shape : public Entity2D
	{
	public:
		Shape(Render* render);
		~Shape();

		void Init(SHAPE_TYPE shapeType);
		void Draw();

	private:
		void BindAttrib();
		void SetShader(unsigned int shaderId) override;
	};
}

#endif // !SHAPE_H