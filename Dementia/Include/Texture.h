#pragma once

#include "Dementia.h"

namespace Dementia{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Clase que conte tot el necesari per dibuixar les textures per pantalla. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class Texture
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor per defecte. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Texture(void);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Destructor. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		virtual ~Texture(void);


		/// <summary>	La Interficie de DirectX encarregada de treballar amb la textura. </summary>
		ID3D11ShaderResourceView*	g_pTextureRV;
	};

}