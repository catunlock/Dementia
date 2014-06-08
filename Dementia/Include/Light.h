#pragma once
#include "Dementia.h"
#include "Entity.h"


namespace Dementia{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	La clase base de la llum. </summary>
///
/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class UTILS_API Light : public Entity
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Els tipus de clases llum derivades que hi han. Aixo serveix per evitar haver de fer
	/// 			un dynamic_cast, que es molt costos a nivell de CPU.
	/// </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	enum LIGHT_TYPE
	{
		DIRECTIONAL_LIGHT,
		SPOT_LIGHT,
		POINT_LIGHT
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor per defecte. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Light(void);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	~Light(void);	
};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Una llum que simular ser de tipus ambient, tots els objectes al scenari es veuen 
	/// 			afectats per aquesta llum. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	struct DirectionalLight
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor per defecte. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		DirectionalLight()
		{	
			ZeroMemory(this, sizeof(this)); 
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor de la llum. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		///
		/// <param name="ambient">  	El color de la llum ambient i la seva intensitat (R,G,B, Intensitat). </param>
		/// <param name="diffuse">  	El color de la llum que reflexan els objectes i la seva intensitat (R,G,B, Intensitat). </param>
		/// <param name="specular"> 	El color de la llum del brillantor dels objectes i la seva intensitat (R,G,B, Intensitat). </param>
		/// <param name="direction">	La direccio des de on ve la llum. </param>
		/// <param name="pad">			Un valor sense cap funcionalitat, que nomes serveix per que la estructura estigui alienada en 16bytes. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		DirectionalLight(XMFLOAT4 ambient, XMFLOAT4 diffuse, XMFLOAT4 specular,	XMFLOAT3 direction, float pad) :
			Ambient(ambient),
			Diffuse(diffuse),
			Specular(specular),
			Direction(direction),
			Pad(pad)
		{ 
		}

		/// <summary>	El color de la llum ambient i la seva intensitat (R,G,B, Intensitat). </summary>
		XMFLOAT4 Ambient;

		/// <summary>	El color de la llum que reflexan els objectes i la seva intensitat (R,G,B, Intensitat). </summary>
		XMFLOAT4 Diffuse;

		/// <summary>	El color de la llum del brillantor dels objectes i la seva intensitat (R,G,B, Intensitat). </summary>
		XMFLOAT4 Specular;

		/// <summary>	La direccio des de on ve la llum. </summary>
		XMFLOAT3 Direction;

		/// <summary>	Un valor sense cap funcionalitat, que nomes serveix per que la estructura estigui alienada en 16bytes. </summary>
		float Pad;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Una llum de tipus punt, que irradia a tots els objectes que estiguin dins del seu 
	/// 			radi d'accio per igual. 
	/// </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	struct PointLight
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor per defecte. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		PointLight() 
		{ 
			ZeroMemory(this, sizeof(this)); 
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor de la llum. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		///
		/// <param name="ambient"> 	El color de la llum ambient i la seva intensitat (R,G,B, Intensitat). </param>
		/// <param name="diffuse"> 	El color de la llum que reflexan els objectes i la seva intensitat (R,G,B, Intensitat). </param>
		/// <param name="specular">	El color de la llum del brillantor dels objectes i la seva intensitat (R,G,B, Intensitat). </param>
		/// <param name="position">	La posicio on es troba la llum. </param>
		/// <param name="range">   	El radi de distancia fins a on arriba la llum. </param>
		/// <param name="att">	   	La atenuacio que va guanyan segons la distancia. </param>
		/// <param name="pad">	   	Un valor sense cap funcionalitat, que nomes serveix per que la estructura estigui alienada en 16bytes. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		PointLight(XMFLOAT4 ambient, XMFLOAT4 diffuse, XMFLOAT4 specular, XMFLOAT3 position, float range, XMFLOAT3 att, float pad) :
			Ambient(ambient),
			Diffuse(diffuse),
			Specular(specular),
			Position(position),
			Range(range),
			Att(att),
			Pad(pad)
		{
		}

		/// <summary>	El color de la llum ambient i la seva intensitat (R,G,B, Intensitat). </summary>
		XMFLOAT4 Ambient;

		/// <summary>	El color de la llum que reflexan els objectes i la seva intensitat (R,G,B, Intensitat). </summary>
		XMFLOAT4 Diffuse;

		/// <summary>	El color de la llum del brillantor dels objectes i la seva intensitat (R,G,B, Intensitat). </summary>
		XMFLOAT4 Specular;

		/// <summary>	La posicio on es troba la llum. </summary>
		XMFLOAT3 Position;

		/// <summary>	El radi de distancia fins a on arriba la llum. </summary>
		float Range;

		/// <summary>	La atenuacio que va guanyan segons la distancia. </summary>
		XMFLOAT3 Att;

		/// <summary>	Un valor sense cap funcionalitat, que nomes serveix per que la estructura estigui alienada en 16bytes. </summary>
		float Pad; 
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Una llum de tipus llinterna o focus, ilumina nomes als objectes en els que la 
	/// 			direccio apunti i estiguin dins del seu radi. 
	/// </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	struct SpotLight
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor per defecte. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		SpotLight() 
		{ 
			ZeroMemory(this, sizeof(this)); 
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor de la llum. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		///
		/// <param name="ambient">  	El color de la llum ambient i la seva intensitat (R,G,B, Intensitat). </param>
		/// <param name="diffuse">  	El color de la llum que reflexan els objectes i la seva intensitat (R,G,B, Intensitat). </param>
		/// <param name="specular"> 	El color de la llum del brillantor dels objectes i la seva intensitat (R,G,B, Intensitat). </param>
		/// <param name="position"> 	La posicio des de on irradia la llum. </param>
		/// <param name="range">		El radi de distancia fins a on arriba la llum. </param>
		/// <param name="direction">	La direccio cap a on apunta la llum. </param>
		/// <param name="spot">			El exponent ultilitzat per controlar la grandia del con de la llum. </param>
		/// <param name="att">			La atenuacio de la llum segons la distancia. </param>
		/// <param name="pad">			Un valor sense cap funcionalitat, que nomes serveix per que la estructura estigui alienada en 16bytes. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		SpotLight(XMFLOAT4 ambient, XMFLOAT4 diffuse, XMFLOAT4 specular, XMFLOAT3 position, float range, XMFLOAT3 direction, float spot, XMFLOAT3 att, float pad) :
			Ambient(ambient),
			Diffuse(diffuse),
			Specular(specular),
			Position(position),
			Range(range),
			Direction(direction),
			Spot(spot),
			Att(att),
			Pad(pad)
		{
		}

		/// <summary>	El color de la llum ambient i la seva intensitat (R,G,B, Intensitat). </summary>
		XMFLOAT4 Ambient;

		/// <summary>	El color de la llum que reflexan els objectes i la seva intensitat (R,G,B, Intensitat). </summary>
		XMFLOAT4 Diffuse;

		/// <summary>	El color de la llum del brillantor dels objectes i la seva intensitat (R,G,B, Intensitat). </summary>
		XMFLOAT4 Specular;

		/// <summary>	La posicio des de on irradia la llum. </summary>
		XMFLOAT3 Position;

		/// <summary>	El radi de distancia fins a on arriba la llum. </summary>
		float Range;

		/// <summary>	La direccio cap a on apunta la llum. </summary>
		XMFLOAT3 Direction;

		/// <summary>	El exponent ultilitzat per controlar la grandia del con de la llum. </summary>
		float Spot;

		/// <summary>	La atenuacio de la llum segons la distancia. </summary>
		XMFLOAT3 Att;

		/// <summary>	Un valor sense cap funcionalitat, que nomes serveix per que la estructura estigui alienada en 16bytes. </summary>
		float Pad;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Entenem per Material una estructura de dades on indiquem quin tipus de llum reflexa 
	/// 			(color i intensitat) els objectes que tenen aquest material. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	struct Material
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor per defecte. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Material()
		{ 
			ZeroMemory(this, sizeof(this)); 
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor del material. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		///
		/// <param name="ambient"> 	El color de la llum ambient que reflexa l'objecte i la seva intensitat. </param>
		/// <param name="diffuse"> 	El color de la llum que diffusa l'objecte i la seva intensitat. </param>
		/// <param name="specular">	El color de la llum de la brillantor de l'objecte i la seva intensitat. </param>
		/// <param name="reflect"> 	El color de la llum que reflexa globalment l'objecte i la seva intensitat. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Material(XMFLOAT4 ambient, 	XMFLOAT4 diffuse, XMFLOAT4 specular, XMFLOAT4 reflect) :
			Ambient(ambient),
			Diffuse(diffuse),
			Specular(specular),
			Reflect(reflect)
		{				
		}


		/// <summary>	El color de la llum ambient que reflexa l'objecte i la seva intensitat. </summary>
		XMFLOAT4 Ambient;

		/// <summary>	El color de la llum que diffusa l'objecte i la seva intensitat. </summary>
		XMFLOAT4 Diffuse;

		/// <summary>	El color de la llum de la brillantor de l'objecte i la seva intensitat. </summary>
		XMFLOAT4 Specular;

		/// <summary>	El color de la llum que reflexa globalment l'objecte i la seva intensitat. </summary>
		XMFLOAT4 Reflect;
	};
}
