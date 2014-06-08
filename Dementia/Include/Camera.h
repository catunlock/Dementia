#pragma once

#include "Dementia.h"

namespace Dementia{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///		Una camara simple pensada per ser ultilitzada com a Primera persona, per explorar la scena 3D.
	///		- Les cordenades de la camara son relatives al systema de espai del mon (World Space).  
	///		  per tant es pot obtenir la Matriu de vista (View Matrix).
	///		- La camara es pot configurar amb les mesures de projeccio per tant es pot obtenir la   
	///		- Matriu de projeccio (Projection Matrix).
	/// </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class UTILS_API Camera
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Crea una camara buida a la posicio X:0.0f Y:0.0f Z:-15.0f . </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Camera();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Destructor. Allibera automaticament tots els recursos.</summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		~Camera();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la posicio on esta situada la camara. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	La posicio on esta situada la camara. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		XMVECTOR GetPosition() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Cambia la posicio de la camara a la nova posicio. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="position">	La nova posicio on es situara la camara. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void SetPosition(XMVECTOR position);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte el vector dret de la camara. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	El vector dret de la camara. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		XMVECTOR GetRight()const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte el vector d'alt de la camara. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	El vector d'alt de la camara. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		XMVECTOR GetUp()const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la direccio cap a on mira la camara.  </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	La direccio cap a on mira la camara. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		XMVECTOR GetLook()const;

		//-----------------------------------------------------------------------------------------------------
		// Get frustum properties.
		//-----------------------------------------------------------------------------------------------------

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la distancia minima a partir de la que es renderitzara en el eix Z . </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	La distancia minima a partir de la que es renderitzara en el eix Z. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		float GetNearZ()const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la distancia maxima a partir de la que es deixa de renderitzar en el eix Z. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	La distancia maxima a partir de la que es deixa de renderitzar en el eix Z. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		float GetFarZ()const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la relacio d'aspecte en el que esta configurada la camara. Es la divisio del
		/// 			ample entre la alcada de la finestra. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	La relacio d'aspecte. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		float GetAspect()const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets fov y coordinate. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	The fov y coordinate. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		float GetFovY()const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets fov x coordinate. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	The fov x coordinate. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		float GetFovX()const;



		float GetNearWindowWidth()const;
		float GetNearWindowHeight()const;
		float GetFarWindowWidth()const;
		float GetFarWindowHeight()const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Configura les lents de la camara. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="fovY">  	El angle de la obertura de visio. </param>
		/// <param name="aspect">	La relacio d'aspecte. </param>
		/// <param name="zn">	 	La distancia minima a partir de la que es comencara a renderitzar. </param>
		/// <param name="zf">	 	La distancia maxima fins a on es renderitzara. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void SetLens(float fovY, float aspect, float zn, float zf);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Defineix l'espai de camera amb la posicio on es troba la camara, cap a on ha de mirar
		/// 			i el vector que apunta cap a d'alt.
		/// 			 </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="pos">	  	La posicio de la camara. </param>
		/// <param name="target"> 	La direccio en la que mira la camara. </param>
		/// <param name="worldUp">	El vector que apunta cap a d'alt. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la matriu de vista (View Matrix). </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	Retorna la matriu de vista. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		XMMATRIX View()const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la matriu de projeccio (Projection Matrix). </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	Retorna la matriu de projeccio. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		XMMATRIX Proj()const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Obte la multiplicacio de la matriu de vista (View Matrix) per la matriu de projeccio 
		/// 			(Projection Matrix). </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <returns>	La multiplicacio de la matriu de vista per la matriu de projeccio. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		XMMATRIX ViewProj()const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Es mou de forma lateral la distancia indicada en el eix de les X. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="d">	La distancia a moures. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void Strafe(float d);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Es mou cap a endevant o endarrera en el eix de les Z. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="d">	La distancia a moures. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void Walk(float d);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Rota la camara en el eix de les X. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="angle">	El angle que es rota. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		
		void Pitch(float angle);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Rota la camara en el eix de les Y. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		///
		/// <param name="angle">	El angle que es rota. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void RotateY(float angle);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Actualitza la matriu de vista (View Matrix). Crida a aquest metode, despres de fer 
		/// 			tots els cambis a la camara, per a que s'actualitzi. </summary>
		///
		/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void UpdateViewMatrix();

	private:


		/// <summary>	La posicio on es troba la camara en la scena. </summary>
		XMVECTOR m_position;

		/// <summary>	El vector dret de la camara. </summary>
		XMVECTOR mRight;

		/// <summary>	El vector d'alt de la camara. </summary>
		XMVECTOR mUp;

		/// <summary>	El vector de direccio que indica cap a on mira la camara. </summary>
		XMVECTOR mLook;

		
		/// <summary>	La distancia minima de visio a partir de la que es comenca a renderitzar. </summary>
		float mNearZ;

		/// <summary>	La distancia maxima de visio a partir de la que es deixa de renderitzar. </summary>
		float mFarZ;

		/// <summary>	La relacio d'aspecte de la projeccio. Normalment es la divisio de l'ample entre la alcada de la finestra. </summary>
		float mAspect;

		/// <summary>	L'angle de visio de amb el que la camara veu el mon. </summary>
		float mFovY;
		
		float mNearWindowHeight;
		float mFarWindowHeight;

		
		/// <summary>	La matriu de vista (View Matrix). </summary>
		XMMATRIX mView;

		/// <summary>	La matriu de projeccio (Projection Matrix). </summary>
		XMMATRIX mProj;
	};

}
