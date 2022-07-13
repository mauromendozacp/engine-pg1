#ifndef LINE_H
#define LINE_H

#include "exports.h"
#include "vertexs.h"
#include "matrix.h"

#include "Renderer/renderer.h"
#include "Color/color.h"

#include <vector>

namespace GL
{
	class GRAPHICSENGINE_API Line
	{
	public:
		Line();
		Line(Render* render);
		Line(std::vector<Vertex> vertexs, Render* render);
		~Line();

		void Init();
		void Draw(glm::mat4 model);
		void DeInit();
		
		std::vector<Vertex> GetVertexs();

		Color color;

	private:
		Render* render;

		uint VAO, VBO;
		std::vector<Vertex> vertexs;

		uint locationPosition;

		uint uniformModel;
		uint uniformView;
		uint uniformProjection;

		uint uniformColor;
		uint uniformAlpha;

		void SetUniforms();
		void UpdateShader(glm::mat4 model);
	};
}

#endif // !LINE_H