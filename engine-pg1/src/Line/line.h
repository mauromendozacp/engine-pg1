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
		Line(std::vector<Vertex> vertexs, std::vector<uint> indexes, Render* render);
		~Line();

		void Init();
		void Draw();
		void DeInit();
		
		void SetVertexs(std::vector<Vertex> vertexs);
		std::vector<Vertex> GetVertexs();

		Color color;

	private:
		Render* render;

		uint VAO, VBO, EBO;
		std::vector<Vertex> vertexs;
		std::vector<uint> indexes;

		uint locationPosition;
		uint locationNormal;
		uint uniformColor;
		uint uniformAlpha;

		void UpdateVertexs();
		void SetUniforms();
		void UpdateShader();
	};
}

#endif // !LINE_H