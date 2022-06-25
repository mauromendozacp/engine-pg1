#ifndef MATERIAL_MANAGER_H
#define	MATERIAL_MANAGER_H

#include "exports.h"
#include "Material/SolidMaterial/solidMaterial.h"
#include "Material/TextureMaterial/textureMaterial.h"

namespace GL
{
	class GRAPHICSENGINE_API MaterialManager
	{
	public:
		MaterialManager();
		~MaterialManager();

		static void Init(Render* render);
		static void DeInit();

		static void SetSolidMaterial(SolidMaterial* solidMat);
		static void SetTextureMaterial(TextureMaterial* textureMat);

		static SolidMaterial* GetSolidMaterial();
		static TextureMaterial* GetTextureMaterial();

	private:
		static SolidMaterial* solidMaterial;
		static TextureMaterial* textureMaterial;
	};
}

#endif // !MATERIAL_MANAGER_H