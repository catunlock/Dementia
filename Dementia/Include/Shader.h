#pragma once

#include "Dementia.h"
#include "Light.h"


namespace Dementia{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Clase que conte tots elements necesaris per treballar amb els shaders. </summary>
///
/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class UTILS_API Shader
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor per defecte. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Shader(void);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	~Shader(void);

public:
	       
	/// <summary>	Interficie de directx que conte totes les dades sobre com es la dispoisicio dels vertexs que ultilitzarem per dibuixar per pantalla </summary>
	ID3D11InputLayout*		g_pVertexLayout;

	/// <summary>	Interficie de DirectX que conte el Vertex Shader. </summary>
	ID3D11VertexShader*     g_pVertexShader;

	/// <summary>	Interficie de DirectX que conte el Pixel Shader. </summary>
	ID3D11PixelShader*      g_pPixelShader;
	
	/// <summary>	Interficie de DirectX que conte un Buffer amb la estructura de dades que se li pasa al shader per actualitzar els valors de dibuixat. </summary>
	ID3D11Buffer*			dx_constantBuffer;
};

}