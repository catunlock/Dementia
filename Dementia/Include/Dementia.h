///Definiciones globales del motor

//#define _XM_NO_INTRINSICS_

#define UTILS_EXPORT

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Excluir material rara vez utilizado de encabezados de Windows

#pragma warning( disable : 4251 )

// Archivos de encabezado de Windows:
#include <windows.h>
#include <windowsx.h>
#include <stdexcept>
#include <d3d11.h>
#include <dxgi.h>
#include <D3Dcompiler.h>
#include <d3dx11.h>
#include <dxerr.h>

#include <fstream>
#include <sstream>
#include <thread>
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <list>
#include <assert.h>
//#define _XM_NO_INTRINSICS_
#include <xnamath.h>
/*
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
*/


#ifdef UTILS_EXPORT
	#define UTILS_API __declspec(dllexport)
#else
	#define UTILS_API __declspec(dllimport)
#endif

//*****************************************************************************
// Simple d3d error checker for book demos.
//*****************************************************************************

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                              \
	{                                                          \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
		}                                                      \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif 

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	*****************************************************************************
/// 	 Macro per a alliberar els Objectes de tipus COM.
/// 	*****************************************************************************.
/// </summary>
///
/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
///
/// <param name="x">	The void to process. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

#define ReleaseCOM(x) { if(x){ x->Release();x = 0; } }

//=============================================================================
// 	 Utils functions
//=============================================================================.

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	Funcio que es crida cuan es produeix un error i tel mostra en l'idioma que te configurat l'usuari.
/// </summary>
///
/// <remarks>	Alberto Lopez Sanchez i Ruben Bagan Benavides, 28/05/2013. </remarks>
///
/// <param name="errorCode">	The error code. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void showErrorMessage(DWORD errorCode);