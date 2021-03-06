#pragma once
#include "Dementia.h"

namespace Dementia{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Clase base per a qualsevol altre clase que hagi de interactuar amb un node i el "Scene Manager" 
/// </summary>
///
/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class UTILS_API Entity
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Els tipus de clase derivades que hi han. Aixo serveix per evitar haver de fer un 
	/// 			dynamic_cast, que es molt costos a nivell de CPU. 
	/// </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	enum TYPE {Light,Mesh};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor per defecte que obliga a tots els objectes derivats dir de quin tipus son. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	///
	/// <param name="type">	El tipus d'objecte derivat. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Entity(TYPE type);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor per defecte. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	~Entity(void);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte l'identificador del objecte. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	///
	/// <returns>	El identificador. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	inline UINT getId () { return m_id; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte el tipus del qual es l'objecte. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	///
	/// <returns>	El tipus del objecte. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	inline TYPE getType () { return m_type; };
private:

	/// <summary>	El tipus d'objecte que es l'objecte derivat que s'ha creat. </summary>
	TYPE m_type;

	/// <summary>	El id del objecte. </summary>
	UINT m_id;
};
}
