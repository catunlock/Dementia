#pragma once
#include "Dementia.h"
#include "Mesh.h"
#include "Entity.h"

namespace Dementia{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Un node es un objecte invisible que se encarrega de sapiguer on, amb quina escala, 
	/// 			i amb quina rotacio s'ha de renderitzar qualsevol entitat.
	/// 			
	/// 			El sistema de nodes es gerarquic, aixo significa que un node pot tenir varis fills i
	/// 			nomes un pare, els nodes fills hereden tots els valors dels pares de forma transparent.
	/// 			
	/// 			Exemple 1: El node pare te escala 5 i el node fill te escala 1, pero el fill ya esta escalat a 5.
	/// 			
	/// 			Exemple 2: El node pare te escala 5 i el node fill te escala 2, 
	/// 			la escala total del node fill es la del pare mes la seva, es a dir 7.
	/// </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class UTILS_API Node
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor per defecte. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		///
		/// <param name="id">	L'identificador del node. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Node	(UINT id);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <param name="id">	   	L'identificador del node. </param>
		/// <param name="position">	La posicio a la que es troba. </param>
		/// <param name="scale">   	La escala que te. </param>
		/// <param name="rotation">	La seva rotacio. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Node	(UINT id, XMVECTOR position, XMVECTOR scale, XMVECTOR rotation);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Destructor. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		~Node	(void);
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte l'identificador del node. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <returns>	L'identificador del node. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline UINT				getId()				{ return m_id; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la posicio relativa al node pare. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <returns>	La posicio relativa al node pare. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline XMVECTOR			getLocalPosition()	{ return m_position; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la escala relativa al node pare. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <returns>	La escala relativa al node pare. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline XMVECTOR			getLocalScale()		{ return m_scale; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la rotacio relativa al node pare. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <returns>	La rotacio relativa al node pare. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline XMVECTOR			getLocalRotation()	{ return m_rotation; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la posicio on es troba el node respecte al mon. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <returns>	La posicio on es troba el node respecte al mon. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline XMVECTOR			getWorldPosition()	{ return m_worldPosition; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la scala total respecte al mon. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <returns>	La scala total respecte al mon. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline XMVECTOR			getWorldScale()		{ return m_worldScale; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la rotacio total respecte al mon. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <returns>	La rotacio total respecte al mon. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline XMVECTOR			getWorldRotation()	{ return m_worldRotation; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte el node pare. El Root Scene Node no te pare.</summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <returns>	El node pare, null si no te pare. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline Dementia::Node*	getParent()				{ return m_parent; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la entitat asociada a aquest node. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <returns>	La entitat asociada a aquest node, null si no en te cap. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline Dementia::Entity*	getEntity()			{ return m_entity; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la matriu de mon (World Matrix) que es la multiplicacio de les seguents matrius:
		/// 				- Translacio (posicio on es troba el node respecte el mon)  
		/// 				- Scala (la scala total del node respecte el mon)   
		/// 				- Rotacio (la rotacio total del node respecte el mon)  
		/// </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <returns>	La matriu de mon (World Matrix). </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		XMMATRIX		getWorldMatrix		(void);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte un vector amb tots els nodes fills del node pasat per parametre.
		/// 			Evitar ultlilitzar aquesta funcio, te un cost de CPU elevat.
		/// </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <param name="nodes">	[in] El node del qual es buesquen tots els fills. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void getAllNodes(std::vector<Dementia::Node*>* nodes);

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Posa o cambia la entitat que te aquest node. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <param name="entity">	[in] La entitat que tindra aquest node. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline void setEntity(Dementia::Entity* entity) { m_entity = entity; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Posa o cambia la posicio que tindra aquest node respecte al node pare  </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <param name="position">	La posicio respecte al node pare. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void			setLocalPosition	(XMVECTOR position);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Posa o cambia la scala que tindra aquest node respecte al node pare. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <param name="scale">	La scala del node. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void			setLocalScale		(XMVECTOR scale);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Posa o cambia la rotacio que tindra aquest node respecte al node pare. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <param name="rotation">	La rotacio del node. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void			setLocalRotation	(XMVECTOR rotation);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Afeigiex un fill al node actual. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <param name="child">	[in] El fill que s'afegira al node. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void			addChild			(Dementia::Node* child);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte el fill a partir de l'id pasat per parametre. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <param name="id">	L'ID del node a buscar. </param>
		///
		/// <returns>	El fill si l'ha trobat, si no torna null. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Dementia::Node* getChild			(UINT id);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Esborra el fill que te l'identificador pasat per parametre. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <param name="id">	L'ID del node a esborrar. </param>
		///
		/// <returns>	true si s'ha esborrat, false si no s'ha trobat. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		bool			removeChild			(UINT id);		
	
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Especifica quin sera el pare de aquet node, si ya en tenia un pare, se li notifica al
		/// 			pare que aquet node deixa de ser fill seu i se li notifica al nou pare que are te
		/// 			aquest fill.
		/// 			
		/// 			Aquesta funcio es privada perque nomes els propis nodes han de poder fer aixo.
		/// </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		///
		/// <param name="parent">	[in] El seu pare. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void			setParent			(Dementia::Node* parent);
	
	private:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Calcula la matriu interna de translacio. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void		calcTranslationMatrix	(void);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Calcula la matriu interna de escala. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void		calcScaleMatrix			(void);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Calcula la matriu interna de rotacio. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void		calcRotationMatrix		(void);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Calcula la matriu interna de mon. </summary>
		///
		/// <remarks>	Rodolfo, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void		calcWorldMatrix			(void);

		void		recalcWorldPosition		(void);
		void		recalcWorldRotation		(void);
		void		recalcWorldScale		(void);

		/// <summary>	El identificador del node. </summary>
		UINT							m_id;

		/// <summary>	La posicio del node respecte al pare. </summary>
		XMVECTOR						m_position;

		/// <summary>	La escala local del node. </summary>
		XMVECTOR						m_scale;

		/// <summary>	La rotacio local del node. </summary>
		XMVECTOR						m_rotation;
			

		/// <summary>	La posicio del node en el mon. </summary>
		XMVECTOR						m_worldPosition;

		/// <summary>	La scala total del node en el mon. </summary>
		XMVECTOR						m_worldScale;

		/// <summary>	La rotaticio total del node en el mon. </summary>
		XMVECTOR						m_worldRotation;


		/// <summary>	La matriu de traslacio. Es una variable cache. </summary>
		XMMATRIX						m_mTranslation;

		/// <summary>	La matriu de escala. Es una variable cache. </summary>
		XMMATRIX						m_mScale;

		/// <summary>	La matriu de rotacio. Es una variable cache. </summary>
		XMMATRIX						m_mRotation;

		/// <summary>	La matriu de mon. Es una variable cache. </summary>
		XMMATRIX						m_mWorld;

		/// <summary>	La entitat que te aquest node asociada. </summary>
		Dementia::Entity*				m_entity;

		/// <summary>	El vector que conte els fills d'aquet node. </summary>
		std::vector<Dementia::Node*>	m_childs;

	private:

		/// <summary>	El node pare. </summary>
		Dementia::Node*					m_parent;
	};

}