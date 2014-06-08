#pragma once
#include "Dementia.h"
#include "Node.h"
#include "Light.h"
#include "Mesh.h"
#include "Texture.h"
#include "Window.h"

namespace Dementia{

	class Window;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Clase encarregada de gestionar tot el relacionat amb tot el que surt per pantalla.
/// 			
/// 			 Crea i destrueix els objectes que es retornen al usuari de manera transparent.
/// </summary>
///
/// <remarks>	Rodolfo, 29/05/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class UTILS_API SceneManager
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	///
	/// <param name="window">	[in] Rep la finestra que el crea.  </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	SceneManager(Dementia::Window* window);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual ~SceneManager(void);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Crea un node. </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	///
	/// <param name="position">	La posicio local del node. </param>
	/// <param name="scale">   	La escala local del node. </param>
	/// <param name="rotation">	La rotacio local del node. </param>
	///
	/// <returns>	El node creat. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Dementia::Node* createNode (XMVECTOR position, XMVECTOR scale, XMVECTOR rotation);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Crea una mesh. </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	///
	/// <param name="geometry">	[in] La geometria asociada. </param>
	///
	/// <returns>	La geometria creada. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Dementia::Mesh* createMesh (Dementia::Geometry* geometry);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Crea un objecte textura. </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	///
	/// <param name="path">	La ruta on es troba la textura que es carregara. </param>
	///
	/// <returns>	El objecte textura. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Dementia::Texture* createTexture(std::wstring path);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Creaa una llum direccional. </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	///
	/// <param name="ambient">  	El color de la llum ambient que reflexa l'objecte i la seva intensitat. </param>
	/// <param name="diffuse">  	El color de la llum que diffusa l'objecte i la seva intensitat. </param>
	/// <param name="specular"> 	El color de la llum de la brillantor de l'objecte i la seva intensitat.. </param>
	/// <param name="direction">	La direccio cap a on apunta la llum. </param>
	///
	/// <returns>	La llum direccional. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	DirectionalLight* createDirectionalLight (
		XMFLOAT4 ambient, XMFLOAT4 diffuse, XMFLOAT4 specular,	XMFLOAT3 direction);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Crea una llum flash/llinterna </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	///
	/// <param name="ambient">  	El color de la llum ambient que reflexa l'objecte i la seva intensitat. </param>
	/// <param name="diffuse">  	El color de la llum que diffusa l'objecte i la seva intensitat. </param>
	/// <param name="specular"> 	El color de la llum de la brillantor de l'objecte i la seva intensitat. </param>
	/// <param name="position"> 	La posicio des de on irradia la llum. </param>
	/// <param name="range">		El radi de distancia fins a on arriba la llum. </param>
	/// <param name="direction">	La direccio cap a on apunta la llum. </param>
	/// <param name="spot">			El exponent ultilitzat per controlar la grandia del con de la llum. </param>
	/// <param name="att">			La atenuacio de la llum segons la distancia. </param>
	///
	/// <returns>	La llum flash/llinterna. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	SpotLight* createSpotLight (
		XMFLOAT4 ambient, XMFLOAT4 diffuse, XMFLOAT4 specular, XMFLOAT3 position, float range, XMFLOAT3 direction, float spot, XMFLOAT3 att);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Crea una llum de punt. </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	///
	/// <param name="ambient"> 	El color de la llum ambient que reflexa l'objecte i la seva intensitat. </param>
	/// <param name="diffuse"> 	El color de la llum que diffusa l'objecte i la seva intensitat. </param>
	/// <param name="specular">	El color de la llum de la brillantor de l'objecte i la seva intensitat. </param>
	/// <param name="position">	La posicio des de on irradia la llum. </param>
	/// <param name="range">   	El radi de distancia fins a on arriba la llum. </param>
	/// <param name="att">	   	La atenuacio de la llum segons la distancia. </param>
	///
	/// <returns>	La llum de punt. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	PointLight* createPointLight (
		XMFLOAT4 ambient, XMFLOAT4 diffuse, XMFLOAT4 specular, XMFLOAT3 position, float range,	XMFLOAT3 att);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Crea un material. </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	///
	/// <param name="ambient"> 	El color de la llum ambient que reflexa l'objecte i la seva intensitat. </param>
	/// <param name="diffuse"> 	El color de la llum que diffusa l'objecte i la seva intensitat. </param>
	/// <param name="specular">	El color de la llum de la brillantor de l'objecte i la seva intensitat. </param>
	/// <param name="reflect"> 	El color de la llum que reflexa globalment l'objecte i la seva intensitat. </param>
	///
	/// <returns>	El material. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Material* createMaterial (XMFLOAT4 ambient, XMFLOAT4 diffuse, XMFLOAT4 specular, XMFLOAT4 reflect);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte el node arrel de la escena. </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	///
	/// <returns>	El node arrel de la escena. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	inline Dementia::Node* getRootSceneNode(void)								{ return m_rootSceneNode; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte tots els models que hi ha al escenari. </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	///
	/// <returns>	Un vector amb tots els models que hi ha al escenari. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	inline std::list<Dementia::Mesh*>* getAllMeshes()							{ return &meshes; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte tots els nodes que hi ha al escenari. </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	///
	/// <returns>	Un vector amb tots els nodes que hi ha al escenari. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	inline std::list<Dementia::Node*>* getAllNodes()							{ return &nodes; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte totes les llums direccionals que hi ha. </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	///
	/// <returns>	Un vector amb totes les llums direccionals que hi ha. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	inline std::list<Dementia::DirectionalLight*>* getAllDirectionalLights()	{ return &directionalLights; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte totes les llums de tipus flash/llinterna. </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	///
	/// <returns>	Un vector amb totes les llums de tipus flash/llinterna. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	inline std::list<Dementia::SpotLight*>* getAllSpotLights()				{ return &spotLights; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte totes les llums de tipus punt. </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	///
	/// <returns>	Un vector amb totes les llums de tipus punt. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	inline std::list<Dementia::PointLight*>* getAllPointLights() { return &pointLights; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Esborra el node amb aquest ID. </summary>
	///
	/// <remarks>	Rodolfo, 30/05/2013. </remarks>
	///
	/// <param name="id">	El identificador. </param>
	///
	/// <returns>	true si l'esborra, false si no. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool removeNode(UINT id);

private:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte l'ultim identificador disponible, per a que no es repeteixin. </summary>
	///
	/// <remarks>	Rodolfo, 29/05/2013. </remarks>
	///
	/// <returns>	El ultim identificador disponible. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	inline UINT getLastId () { return m_id++; };

	/// <summary>	El comptador de IDs. </summary>
	UINT m_id;

	/// <summary>	La referencia a la finestra que s'ha creat. </summary>
	Dementia::Window* m_window;

	/// <summary>	La textura per defecte per als models que no tenen textura. </summary>
	Dementia::Texture* defaultTexture;

	/// <summary>	El vector de nodes que hi ha a la escena. </summary>
	std::list<Dementia::Node*> nodes;

	/// <summary>	El vector de models que hi ha a la escena. </summary>
	std::list<Dementia::Mesh*> meshes;

	/// <summary>	El vector de textures que hi ha a la escena. </summary>
	std::list<Dementia::Texture*> textures;


	/// <summary>	El vector de llums direccionals que hi ha a la escena.</summary>
	std::list<Dementia::DirectionalLight*> directionalLights;

	/// <summary>	El vector de llums flash/llinterna que hi ha a la escena. </summary>
	std::list<Dementia::SpotLight*> spotLights;

	/// <summary>	El vector de llums de punt que hi ha a la escena. </summary>
	std::list<Dementia::PointLight*> pointLights;

	/// <summary>	El node arrel de la escena. </summary>
	Dementia::Node* m_rootSceneNode;
};
}
