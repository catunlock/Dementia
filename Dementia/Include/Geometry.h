#pragma once

#include "Dementia.h"


namespace Dementia{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Entenem per geometria el conjunt de vertex i index que calen per formar una figura
	/// 			geometrica. 
	/// </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class UTILS_API Geometry
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Conte tots els elements necesaris per fer tots els calculs per pantalla(llums, etc).
		/// </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		struct Vertex
		{
			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Constructor per defecte. </summary>
			///
			/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			Vertex(){}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Constructor. </summary>
			///
			/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
			///
			/// <param name="p"> 	La posicio del vertex relativa al seu espai local. </param>
			/// <param name="n"> 	La direccio cap a on mira aquest vertex. </param>
			/// <param name="t"> 	La tangent d'aquest vertex. </param>
			/// <param name="uv">	Les cordenades de la textura com s'ha d'aplicar fins a aquest vertex. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			Vertex(const XMFLOAT3& p, const XMFLOAT3& n, const XMFLOAT3& t, const XMFLOAT2& uv)
				: Position(p), Normal(n), TangentU(t), TexC(uv){}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Constructor. </summary>
			///
			/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
			///
			/// <param name="px">	Camp X de la posicio. </param>
			/// <param name="py">	Camp Y de la posicio. </param>
			/// <param name="pz">	Camp Z de la posicio. </param>
			/// <param name="nx">	Camp X del "normal". </param>
			/// <param name="ny">	Camp Y del "normal". </param>
			/// <param name="nz">	Camp Z del "normal". </param>
			/// <param name="tx">	Camp X de la tangent. </param>
			/// <param name="ty">	Camp Y de la tangent. </param>
			/// <param name="tz">	Camp Z de la tangent. </param>
			/// <param name="u"> 	Camp U de la cordenada de textura. </param>
			/// <param name="v"> 	Camp V de la cordenada de textura. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			Vertex(
				float px, float py, float pz, 
				float nx, float ny, float nz,
				float tx, float ty, float tz,
				float u, float v)
				: Position(px,py,pz), Normal(nx,ny,nz),
				  TangentU(tx, ty, tz), TexC(u,v){}

			/// <summary>	La posicio del vertex relativa al seu espai local. </summary>
			XMFLOAT3 Position;

			/// <summary>	El normal del vertex. </summary>
			XMFLOAT3 Normal;

			/// <summary>	La tangent del vertex. </summary>
			XMFLOAT3 TangentU;

			/// <summary>	Les cordenades de textura. </summary>
			XMFLOAT2 TexC;
		};

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor per defecte. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Geometry();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Destructor. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		~Geometry(void);
	

		/// <summary>	Els vertex de aquesta geometria. </summary>
		std::vector<Vertex> Vertices;

		/// <summary>	Els indexos de aquesta geometria. </summary>
		std::vector<UINT> Indices;


		/// <summary>	Buffer de DirectX11 dels vertex. </summary>
		ID3D11Buffer* vb;


		/// <summary>	Buffer de DirectX11 dels indexos. </summary>
		ID3D11Buffer* ib;
	};

}