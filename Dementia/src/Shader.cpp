#include "Shader.h"

namespace Dementia{

Shader::Shader(void) :
	g_pVertexLayout(NULL),
	g_pVertexShader(NULL),
	g_pPixelShader(NULL),
	dx_constantBuffer(NULL)
{
}

Shader::~Shader(void)
{
	ReleaseCOM(g_pVertexLayout);
	ReleaseCOM(g_pVertexShader);
	ReleaseCOM(g_pPixelShader);
	ReleaseCOM(dx_constantBuffer);
}



	

}