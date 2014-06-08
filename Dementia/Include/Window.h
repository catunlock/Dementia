////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	Window.h
//
// summary:	Declara la clase Window.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Dementia.h"
#include "DX11.h"
#include "Node.h"
#include "InputManager.h"
#include "GameTimer.h"
#include "Camera.h"
#include "SceneManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// namespace: Dementia
///
/// <summary> El espai de nom principal del framework. Totes les clases basiques o importants es 
/// 		  troben aqui dins.
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Dementia
{
	class DX11;
	class SceneManager;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Clase encarregada de gestionar tot el relacionat amb la finestra a nivell de
	/// 			Sistema Operatiu i conte tots el elements necesaris per ultilitzar el framework.
	/// 			
	/// 			Cada finestra es considera com un escenari totalment independent.
	/// </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 12/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class UTILS_API Window
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Contructor. Per inicialitzar la finestra crida al metode init(). </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="id">	   	El identificador de la finestra. Ha de ser unic. </param>
		/// <param name="width">   	El ample. </param>
		/// <param name="height">  	La alcada. </param>
		/// <param name="title">   	El titul que veura l'usuari. </param>
		/// <param name="vsync">   	Indica si el refresc de la finestra estara sincronitzat amb el refresc del monitor. </param>
		/// <param name="windowed">	Indica si la finestra es creara a pantalla completa o no. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Window(UINT id, UINT width, UINT height, std::wstring title, bool vsync, bool windowed);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Destructor. Allibera tots els recursos automaticament. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		virtual ~Window();
	private:
		
		/// <summary>	La implementacio de Directx. </summary>
		Dementia::DX11* m_dx11;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Ininicialitza la finestra i tots els seus components. La crea i la mostra per pantalla. 
		/// 			Tambe inicialitza la implementacio grafica (DirectX o OpenGL).
		/// </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void init();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Allibera tots els recursos de la finestra. no cal cridar-lo. Es crida automaticament
		/// 			quan es destrueix la finestra. 
		/// </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void release(void);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Executa el bucle principal de la finestra. S'ha de fer en bucle per mantenir la 
		/// 			execucio. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="exitCode">	[out] Retorna el codi de sortida de la finestra. Tan si ha terminat 
		/// 						correctament com si no. 
		/// </param>
		///
		/// <returns>	true si es continua executant. false si s'ha acabat la execucio. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		bool run(int* exitCode); //Devuelve si aun se esta ejecutando la ventana

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Cambia el color de fons de la finestra. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="backgroundColor">	El color de fons. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void setBackgroundColor(XMVECTOR backgroundColor);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Posa la finestra a mode finestra o a pantalla completa. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="state">	true per mode finestra. false per mode a pantalla completa </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline void setWindowed(bool state)						 { m_windowed = state; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Cambia la altura de la finestra. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="height">	La nova altura. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline void setHeight(UINT height)						 { m_height = height; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Cambia l'ample de la finestra. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="width">	El nou ample. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline void setWidth(UINT width)						 { m_width = width; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Cambia el titul de la finestra. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="title">	El nou titol. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline void setTitle(std::wstring title)				 { m_title = title; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Cambia l'estat de la sincronitzacio vertical. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="state">	true activa la sincronitzacio vertical, false la desactiva. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline void setVsync(bool state)						 { m_vsync = state; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Retorna el color de fons de la finestra. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	El color de fons. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		XMVECTOR getBackgroundColor();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Pregunta si la finestra esta en mode finestra o a pantalla completa. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	true  si esta en mode finestra, false si esta a pantalla completa. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline bool isWindowed ()								 { return m_windowed; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Pregunta si la sincronitzacio vertical esta activada. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	true si la sincronitzacio vertical esta activada, false si no ho esta. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline bool isVsync ()									 { return m_vsync; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Pregunta si la finestra esta pausada. La finestra es pausa automaticament 
		/// 			quan perd el focus i es torna a reanudar cuan torna a tenir el focus. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	true si esta pausada. false si no ho esta. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline bool isPaused ()									 { return m_appPaused; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la alcada de la finestra. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	La alcada de la finestra. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline UINT getHeight()									 { return m_height; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la amplada de la finestra.  </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	La amplada de la finestra. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline UINT getWidth()									 { return m_width; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte l'identificador de la finestra. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	L'identificador de la finestra. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline UINT getId()										 { return m_id; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte el titul de la finestra. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	El titul de la finestra. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline std::wstring getTitle()							 { return m_title; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte el "handle" de la finestra. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	El "handle" de la finestra. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline HWND getWindowHandle()							 { return m_hWindow; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte el Input Manager. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	El objecte Input Manager. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline Dementia::InputManager* getInputManager()		 { return &m_inputManager; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte el Game Timer. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	El objecte Game Timer. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		inline Dementia::GameTimer* getGameTimer()				 { return &m_timer; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la camara. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	El objecte Camera. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Dementia::Camera*		getCamera();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte el "Scene Manager" </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	El objecte Scene Manager. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Dementia::SceneManager* getSceneManager();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte el Dispositiu Graphic DirectX 11. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	Retorna el objecte ID3D11Device de la implementacio grafica. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		ID3D11Device*			getDevice();

	private:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Inicialitza la part de sistema operatiu de la finestra. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	El "handle" de la finestra. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		HWND initWindow(void);
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Sencarrega de processas els missatges que envia el sistema operatiu a la finestra. 
		/// </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="msg">   	El message. </param>
		/// <param name="wParam">	El camp wParam del missatge. </param>
		/// <param name="lParam">	El camp lParam del missatge. </param>
		///
		/// <returns>	El resultat del procesament del missatge. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		LRESULT msgProc(UINT msg, WPARAM wParam, LPARAM lParam);

	private:

		/// <summary>	El identificador de la finestra. </summary>
		UINT m_id;

		/// <summary>	El ample de la finestra. </summary>
		UINT m_width;

		/// <summary>	La alcada de la finestra. </summary>
		UINT m_height;

		/// <summary>	El titul de la finestra. </summary>
		std::wstring m_title;
		

		/// <summary>	El "Handle" de la finestra. </summary>
		HWND m_hWindow;

		/// <summary>	La instancia de la aplicacio principal. </summary>
		HINSTANCE m_hInstance;
	

		/// <summary>	true si la finestra esta pausada. </summary>
		bool m_appPaused;

		/// <summary>	true si la finestra esta minimitzada. </summary>
		bool m_Minimized;

		/// <summary>	true si la finestra esta maximitzada. </summary>
		bool m_Maximized;
		
		/// <summary>	true si es te que redimensionar la finestra. </summary>
		bool m_resizing;

		/// <summary>	true si la sincronitzacio vertical esta activada. </summary>
		bool m_vsync;

		/// <summary>	true si la finestra esta en mode finestra (no en pantalla completa). </summary>
		bool m_windowed;

		/// <summary>	true si la finestra s'ha initcialitzat correctament. </summary>
		bool m_init;
		

		/// <summary>	El "Scene Manager". </summary>
		Dementia::SceneManager* m_sceneManager;

		/// <summary>	El "Input Manager". </summary>
		Dementia::InputManager m_inputManager;

		/// <summary>	El "Game Timer". </summary>
		Dementia::GameTimer m_timer;
	};

}
