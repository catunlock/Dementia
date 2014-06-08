#include "Texture.h"

namespace Dementia{

	Texture::Texture(void)
	{

	}


	Texture::~Texture(void)
	{
		if(g_pTextureRV != nullptr)
		{
			delete g_pTextureRV;
		}
	}

}