#pragma once

#include "Dementia.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace Dementia{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Clase encarregada de gestionar tots els dispositius de entrada entre l'usuari i el 
	/// 			sistema operatiu 
	/// </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class UTILS_API InputManager
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Constructor per defecte. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		InputManager(void);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Destructor. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		virtual ~InputManager(void);

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la instancia del objecte "Mouse". </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		///
		/// <returns>	La instancia del objecte "Mouse". </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline Mouse* getMouse() { return &mouse; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la instancia del objecte "Keyboard". </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		///
		/// <returns>	La instancia del objecte "Keyboard". </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline Keyboard* getKeyboard() { return &keyboard; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Processa tots els events que tenen que pugin ser de entrada de l'usuari.
		/// 			No s'ha de cridar a aquesta funcio a no ser que s'apigues el que estas fent.
		/// </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
		///
		/// <param name="msg">   	El missatge a processar. </param>
		/// <param name="wParam">	El camp wParam del missatge. </param>
		/// <param name="lParam">	El camp lParam del missatge. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void processEvent(UINT msg, WPARAM wParam, LPARAM lParam);
	private:

		/// <summary>	La instancia del teclat. </summary>
		Keyboard keyboard;

		/// <summary>	La instancia del ratoli. </summary>
		Mouse mouse;
	};

}