////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	GameTimer.h
//
// summary:	Declares the game timer class
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Dementia.h"

namespace Dementia{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	S'encarrega de controlar tot el que te a veure amb el temps. </summary>
///
/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 14/05/2013. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class UTILS_API GameTimer
{
public:
	GameTimer();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte el total de temps que ha pasat des de que s'ha initcialitzat la finestra.
	/// 			El temps que ha pasat en pausa, no compta.
	/// </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 12/05/2013. </remarks>
	///
	/// <returns>	El total de temps des de que s'ha inicialitzat la finestra. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	float getGameTime()const;  // in seconds
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte el temps que pasa entre que es renderitza la imatge actual i la anterior. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 12/05/2013. </remarks>
	///
	/// <returns>	El temps delta. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	float getDeltaTime()const; // in seconds

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Reinicia el temps de joc a 0. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 12/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void reset();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Comeca a comptar el temps de joc. Si estaba en stop continua des de l'ultim punt.			
	/// </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 12/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void start();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Para de comptar el temps de joc. No posa el comptador a 0. Si es crida a al metode
	/// 			start() es retorna des de aquet punt.
	///  </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 12/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void stop();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Compta les imatges per segon. S'ha de cridar cada imatge </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 12/05/2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void tick();

private:
	/// <summary>	El temps ultlitzat per cada tick del processador. </summary>
	double mSecondsPerCount;
	/// <summary>	El temps entre els dos ultims frames. </summary>
	double mDeltaTime;
	/// <summary>	El temps base del comptador. </summary>
	__int64 mBaseTime;
	/// <summary>	La cuantitat de temps que el joc ha estat pausat. </summary>
	__int64 mPausedTime;
	/// <summary>	El moment en el que el comptador a sigut parat. </summary>
	__int64 mStopTime;
	/// <summary>	El moment en el que s'ha renderitzat la imatge anterior. </summary>
	__int64 mPrevTime;
	/// <summary>	El moment en el que s'ha renderitzat la imatge actual. </summary>
	__int64 mCurrTime;

	/// <summary>	true si esta parat. </summary>
	bool mStopped;
};

}