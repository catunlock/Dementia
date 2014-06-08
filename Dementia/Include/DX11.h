#pragma once

#include "Dementia.h"
#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "MathHelper.h"
#include "SceneManager.h"
#include "Entity.h"

namespace Dementia{  

	class Window;

	class UTILS_API DX11
	{
	public:
		DX11(Dementia::Window* window);
		virtual ~DX11(void);

	public:
		void* operator new (size_t size){
			void * p = _aligned_malloc(size, 16);
			if (p == 0)  throw std::bad_alloc();
			return p;
		}

			void operator delete (void *p) {
				DX11* pc = static_cast<DX11*>(p);
				_aligned_free(p);
		}
	public:
		inline void setBackgroundColor(XMVECTOR backgroundcolor) { m_backgroundColor = backgroundcolor; };
		inline XMVECTOR getBackgroundColor() { return m_backgroundColor; };
		inline Dementia::Camera* getCamera() { return &m_camera; };

	private:
		Dementia::Window* m_window;
		XMVECTOR m_backgroundColor;

		// BASURACA

	public:	
		void			close();
		void			updateScene(float delta);
		void			drawScene();
		void			onResize();

		ID3D11Device*	getDevice();
		LRESULT DX11::msgProc(UINT msg, WPARAM wParam, LPARAM lParam);
	
		struct ConstantBuffer
		{
			XMMATRIX mWorld;
			XMMATRIX mView;
			XMMATRIX mProjection;
			DirectionalLight gDirLight;
			PointLight gPointLight;
			SpotLight gSpotLight;
			Material gMaterial;
			XMFLOAT3 gEyePosW;
			float pad;
		};
	// Metodos privados de la clase
	private:
		HWND initWindow();
		void initDirectX();
		void buildVertexLayout();

		void createAdapterLog(std::wstring logName,IDXGIFactory *factory);
		void BuildSamplerDesc();


		
	// Variables de Windows
	private:
		static HINSTANCE	m_hAppInstance;
	

	// Variables de DirectX 11.
	private:
		D3D_DRIVER_TYPE m_driverType;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_immediateContext;
	
		D3D_PRIMITIVE_TOPOLOGY m_primitiveTopology;
		ID3D11InputLayout* m_inputLayout;
	
		ConstantBuffer m_cb;
		Shader m_defaultShader;
		ID3D11SamplerState* m_defaultSamplerState;

		UINT stride;
		UINT offset;

		IDXGISwapChain*  m_swapChain;
		ID3D11RenderTargetView* m_renderTargetView;
		ID3D11DepthStencilView* m_depthStencilView;
		ID3D11Texture2D* m_depthStencilBuffer;
		D3D11_VIEWPORT m_screenViewport;

	// Variables privadas de la clase
	private:

		UINT m_4xMsaaQuality;
		bool m_enable4xMsaa;
	
	//Variables de shader manager
	private:

		HRESULT DX11::BuildShader(std::wstring path, Shader* shaderOutput);

	public:

	// Variables Perifericos
	private:

		Dementia::Camera m_camera;

	// Variables de Luz
	private:
		DirectionalLight mDirLight;
		PointLight mPointLight;
		SpotLight mSpotLight;
		Material mLandMat;
		Material mWavesMat;
	};

}