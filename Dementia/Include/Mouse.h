#pragma once

#include "Dementia.h"


namespace Dementia
{
////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Classe encarregada del ratoli que fa de intermediari entre l'usuari i el Sistema 
/// 			Operatiu </summary>
///
/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 14/05/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class UTILS_API Mouse
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Els possibles buttons dels cuals es pot monitoritzar el seu estat. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 14/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	enum Button {

		/// <summary>	El Boto dret del ratoli. </summary>
		Right,

		/// <summary>	El boto esquerra del ratoli. </summary>
		Left,

		/// <summary>	El boto central del ratoli. </summary>
		Middle,

		/// <summary>	El Buto4 del ratoli, normalment es un dels buttons laterals. </summary>
		Button4,

		/// <summary>	El Buto4 del ratoli, normalment es un dels buttons laterals. </summary>
		Button5,

		/// <summary>	El numero de elements que te el enum. </summary>
		COUNT
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor per defecte. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 14/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Mouse(void);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor que inicialitza el ratoli a una posicio concreta.
	/// 			Al initzialitzar es moura el ratoli a la posicio especificada. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 14/05/2013. </remarks>
	///
	/// <param name="x">	La coordenada X. </param>
	/// <param name="y">	La coordenada Y. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Mouse(float x, float y);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 14/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual ~Mouse(void);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte la posicio actual on es troba el ratoli. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 14/05/2013. </remarks>
	///
	/// <returns>	La posicio. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	XMFLOAT2 getPosition();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Posa el ratoli a una posicio concreta de la pantalla. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 14/05/2013. </remarks>
	///
	/// <param name="newPosition">	La nova posicio. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void setPosition(XMFLOAT2 newPosition);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Actualitza la variable interna de posicio del ratoli de la clase. No mou el ratoli
	/// 			a la nova posicio. Aquest metode no s'ha de ultilitzar a no ser que sapigues que 
	/// 			estas fent. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 14/05/2013. </remarks>
	///
	/// <param name="newPosition">	La nova posicio. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void updatePosition(XMFLOAT2 newPosition);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Posa el boto pasat per parametre com pulsat. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 14/05/2013. </remarks>
	///
	/// <param name="buttonPressed">	El boto que es marcara com pulsat. </param>
	/// <param name="position">			La posicio on s'ha pulsat el boto. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void setButtonPressed(Button buttonPressed, XMFLOAT2 position);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Posa el boto pasat per parametre com a lliberat. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 14/05/2013. </remarks>
	///
	/// <param name="buttonReleased">	El boto que es marcara com a lliberat. </param>
	/// <param name="position">		 	La posicio on s'ha alliberat el boto. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void setButtonReleased(Button buttonReleased, XMFLOAT2 position);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Pregunta si el boto pasat per parametre esta pulsat. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 14/05/2013. </remarks>
	///
	/// <param name="button">	El boto per el qual preguntes. </param>
	///
	/// <returns>	true si el boto per el qual preguntes esta pulsat, false si no ho esta. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool isButtonPressed(Button button);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Pregunta si el ratoli s'ha mogut des de la ultima vegada que s'ha cridat al metode
	/// 			getPosition. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 14/05/2013. </remarks>
	///
	/// <returns>	true si s'ha mogut, false si no. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool isMoved();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	L'indica el ratoli on es troba el centre de la finestra. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
	///
	/// <param name="center">	El centre de la finestra. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void setCenter(XMFLOAT2 center);

private:

	/// <summary>	guarda quins botons estan pulsats i quins no. </summary>
	bool pressedButtons[Button::COUNT];

	/// <summary>	guarda si s'ha mogut des de la ultima vegada que s'ha cridat al getPosition </summary>
	bool moved;

	/// <summary>	La posicio del ratoli. </summary>
	XMFLOAT2 position;

	/// <summary>	El centre de la finestra. </summary>
	XMFLOAT2 m_center;
};

}

