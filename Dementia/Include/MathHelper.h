#pragma once

#include "Dementia.h"

namespace Dementia{

class UTILS_API MathHelper
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte un numero aleatori float entre 0 i 1. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	///
	/// <returns>	El numero aleatori entre 0 i 1. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static float RandF()
	{
		return (float)(rand()) / (float)RAND_MAX;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte un numero aleatori float entre a i b. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	///
	/// <param name="a">	El numero minim que retornara. </param>
	/// <param name="b">	El numero maxim que retornara. </param>
	///
	/// <returns>	Un numero aleatori float entre a i b. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	static float RandF(float a, float b)
	{
		return a + RandF()*(b-a);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Determina el minim entre els 2 parametres. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	///
	/// <typeparam name="typename T">	Type of the typename t. </typeparam>
	/// <param name="a">	El limit de la comprobacio. </param>
	/// <param name="b">	El valor a comprobar. </param>
	///
	/// <returns>	Si el parametre b es mes gran que el parametre a, retorna el parametre B, si no 
	/// 			retorna el parametre A. 
	/// </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	static T Min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Determina el maxim entre els 2 parametres. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	///
	/// <typeparam name="typename T">	Type of the typename t. </typeparam>
	/// <param name="a">	El limit de la comprobacio. </param>
	/// <param name="b">	El valor a comprobar. </param>
	///
	/// <returns>	Si el parametre B es mes petit que el parametre a, retorna el parametre B, si no
	/// 			retorna el parametre A. 
	/// </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	static T Max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}
	

	template<typename T>
	static T Lerp(const T& a, const T& b, float t)
	{
		return a + (b-a)*t;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Comproba que el valor x no es pasa ni per sobre ni per sota. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	///
	/// <typeparam name="typename T">	Type of the typename t. </typeparam>
	/// <param name="x">   	El valor a comprobar. </param>
	/// <param name="low"> 	El valor minim. </param>
	/// <param name="high">	El valor maxim. </param>
	///
	/// <returns>	Si el valor es mes petit que el minim retorna el minim, si es mes gran que el maxim
	/// 			retorna el maxim, si no es cap dels dos retorna el valor. 
	/// </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	static T Clamp(const T& x, const T& low, const T& high)
	{
		return x < low ? low : (x > high ? high : x); 
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte el angle polar del punt (x,y) en [0, 2*PI]. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	///
	/// <param name="x">	La coordenada X. </param>
	/// <param name="y">	La coordenada Y. </param>
	///
	/// <returns>	El angle calculat dels 2 punts. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	static float AngleFromXY(float x, float y);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Obte la matriu inversa i transposada a la pasada per parametre. </summary>
	///
	/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 29/05/2013. </remarks>
	///
	/// <param name="M">	La matriu a processar. </param>
	///
	/// <returns>	La matriu invertida i transposada. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static XMMATRIX InverseTranspose(CXMMATRIX M)
	{
		XMMATRIX A = M;
		A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		XMVECTOR det = XMMatrixDeterminant(A);
		return XMMatrixTranspose(XMMatrixInverse(&det, A));
	}

	static XMVECTOR RandUnitVec3();
	static XMVECTOR RandHemisphereUnitVec3(XMVECTOR n);


	/// <summary>	Esta considerat com el maxim valor que pot agafar un float, cambia segons el sistema. </summary>
	static const float Infinity;

	/// <summary>	Valor predeterminat de pi. </summary>
	static const float Pi;

};

}
