// stdafx.h: archivo de inclusi�n de los archivos de inclusi�n est�ndar del sistema
// o archivos de inclusi�n espec�ficos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once

#define UTILS_EXPORT

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Excluir material rara vez utilizado de encabezados de Windows

// Archivos de encabezado de Windows:
#include <windows.h>
#include <windowsx.h>
#include <stdexcept>
#include <d3d11.h>
#include <dxgi.h>
#include <D3Dcompiler.h>
#include <d3dx11.h>
#include <dxerr.h>
#include "d3dx11effect.h"

#include <fstream>
#include <sstream>
#include <thread>
#include <string>
#include <memory>
#include <iostream>
#include <vector>
//#define _XM_NO_INTRINSICS_

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>


#include "GameTimer.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Node.h"
#include "InputManager.h"
#include "MouseImpl.h"
#include "Geometry.h"
#include "Camera.h"
#include "GeometryFactory.h"
#include "MathHelper.h"
#include "Shader.h"
#include "Window.h"
#include "DX11.h"








// TODO: mencionar aqu� los encabezados adicionales que el programa necesita
