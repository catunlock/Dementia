#include "DX11.h"


namespace Dementia{  

DX11::DX11(Dementia::Window* window) :
	m_window(window),
	m_backgroundColor(XMVectorSet(0.22745f, 0.79607f, 0.73725f, 1.0f)),
	m_swapChain(0), 
	m_renderTargetView(0), 
	m_depthStencilBuffer(0),
	m_depthStencilView(0), 
	m_primitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST),
	m_4xMsaaQuality(0),
	m_enable4xMsaa(false),
	stride(sizeof(Geometry::Vertex)),
	offset(0)
{	
	initDirectX();
	onResize();
	BuildShader(L"shader.fx", &m_defaultShader);
	BuildSamplerDesc();
}


DX11::~DX11(void)
{
	close();
}

void DX11::close()
{
	ReleaseCOM(m_renderTargetView);
	ReleaseCOM(m_depthStencilView);
	ReleaseCOM(m_swapChain);
	ReleaseCOM(m_depthStencilBuffer);

	if(m_immediateContext)
	{
		m_immediateContext->ClearState();
	}
	
	ReleaseCOM(m_immediateContext);
	ReleaseCOM(m_device);

}

ID3D11Device* DX11::getDevice()
{
	return m_device;
}

void DX11::initDirectX()
{
	/* Creació del "Device" i del "Context" Dx 11 */
	UINT deviceFlags = 0;
	#if defined(DEBUG) || defined(_DEBUG)
		deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	D3D_FEATURE_LEVEL featureLevel;

	HRESULT hr = D3D11CreateDevice (
		0,							// Adaptador per defecte
		D3D_DRIVER_TYPE_HARDWARE,	// Driver Type
		NULL,						// Emulació de Dx per Software Null = 0
		deviceFlags,				// Flags 
		NULL,						// Conte un array de nivell de "Features level support", NULL = el nivell de "Feature" més elevat de la gràfica disponible
		0,							// Nombre de elements que hi ha en el array de "Features level support", 0 = si s'ha especificat NULL en l'anterior paràmetre.
		D3D11_SDK_VERSION,			// Versió del SDK
		&m_device,					// Retorna el "Device" creat
		&featureLevel,				// Retorna la "Feature level" suportada
		&m_immediateContext			// Retorna el "Context" creat
	);
		
	#if defined(DEBUG) || defined(_DEBUG)
		if (featureLevel != D3D_FEATURE_LEVEL_11_0)
		{
			std::cout << "La targeta gràfica no suporta Dx 11!" << std::endl;
		}

		switch (featureLevel)
		{
		case D3D_FEATURE_LEVEL_9_1:
			std::cout << "La targeta gràfica supporta Dx 9.1!" << std::endl;
			break;
		case D3D_FEATURE_LEVEL_9_2:
			std::cout << "La targeta gràfica supporta Dx 9.2!" << std::endl;
			break;
		case D3D_FEATURE_LEVEL_9_3:
			std::cout << "La targeta gràfica supporta Dx 9.3!" << std::endl;
			break;
		case D3D_FEATURE_LEVEL_10_0:
			std::cout << "La targeta gràfica supporta Dx 10!" << std::endl;
			break;
		case D3D_FEATURE_LEVEL_10_1:
			std::cout << "La targeta gràfica supporta Dx 10.1!" << std::endl;
			break;
		case D3D_FEATURE_LEVEL_11_0:
			std::cout << "La targeta gràfica supporta Dx 11!" << std::endl;
			break;
		default:
			break;
		}
	#endif

	HR(m_device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality));
	
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width  = m_window->getWidth();
	sd.BufferDesc.Height = m_window->getHeight();
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Comprova si s'ha de utilitzar el MSAA o no
	if (m_enable4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		sd.SampleDesc.Count   = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount  = 1;
	sd.OutputWindow = m_window->getWindowHandle();
	sd.Windowed     = m_window->isWindowed();
	sd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags        = 0;

	IDXGIDevice* dxgiDevice = 0;
	HR(m_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));
	      
	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	HR(dxgiFactory->CreateSwapChain(m_device, &sd, &m_swapChain));
	
	createAdapterLog(L"LogAdaptadors.txt",dxgiFactory);


	ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);
	

	onResize();

	BuildShader(std::wstring(L"shader.fx"), &m_defaultShader);
    
	m_immediateContext->IASetPrimitiveTopology(m_primitiveTopology); //El TriangleList Fijo
	m_immediateContext->IASetInputLayout(m_defaultShader.g_pVertexLayout); //El tipo de vertice que vamos a usar

		// Setup our lighting parameters
	// Directional light.
	mDirLight.Ambient  = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	mDirLight.Diffuse  = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mDirLight.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mDirLight.Direction = XMFLOAT3(0.57735f, -0.57735f, 0.57735f);
 
	// Point light--position is changed every frame to animate in UpdateScene function.
	mPointLight.Ambient  = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	mPointLight.Diffuse  = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	mPointLight.Specular = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	mPointLight.Att      = XMFLOAT3(0.0f, 0.1f, 0.0f);
	mPointLight.Range    = 15.0f;

	// Spot light--position and direction changed every frame to animate in UpdateScene function.
	mSpotLight.Ambient  = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mSpotLight.Diffuse  = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);
	mSpotLight.Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mSpotLight.Att      = XMFLOAT3(1.0f, 0.0f, 0.0f);
	mSpotLight.Spot     = 96.0f;
	mSpotLight.Range    = 10000.0f;

	mLandMat.Ambient  = XMFLOAT4(0.48f, 0.77f, 0.46f, 1.0f);
	mLandMat.Diffuse  = XMFLOAT4(0.48f, 0.77f, 0.46f, 1.0f);
	mLandMat.Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 16.0f);

	mWavesMat.Ambient  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mWavesMat.Diffuse  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mWavesMat.Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mWavesMat.Reflect = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
}

void DX11::createAdapterLog (std::wstring logName, IDXGIFactory *factory)
{	
	IDXGIAdapter* dxgiAdapter = 0;
	IDXGIOutput* dxgiOutput = 0;
	DXGI_ADAPTER_DESC mAdapterDesc;
	
	UINT indexAdapter = 0;
	UINT indexOutput = 0;
	UINT outputNum = 0;
	
	std::wofstream log;
		
	log.open(logName);
	log << "\t ============== Registre dels adaptadors disponibles ==============" << std::endl;
	while (factory->EnumAdapters(indexAdapter,&dxgiAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		dxgiAdapter->GetDesc(&mAdapterDesc);
		log << "\t\t===== Adaptador Numero " << indexAdapter << " =====" << std::endl;
		log << "\tNom/Descripció fabricant: " << mAdapterDesc.Description << std::endl;
		log << "\tId venedor: " << mAdapterDesc.VendorId << std::endl;
		log << "\tId device: " << mAdapterDesc.DeviceId << std::endl;
		log << "\tId subSys: " << mAdapterDesc.SubSysId << std::endl;
		log << "\tRevisió: " << mAdapterDesc.Revision << std::endl;
		log << "\tMemòria de video dedicada: " << mAdapterDesc.DedicatedVideoMemory << std::endl;
		log << "\tMemòria del sistema dedicada: " << mAdapterDesc.DedicatedSystemMemory << std::endl;
		log << "\tMemòria del sistema compartida: " << mAdapterDesc.SharedSystemMemory << std::endl;
		log << "\tId adapter (High Part): " << mAdapterDesc.AdapterLuid.HighPart << std::endl;
		log << "\tId adapter (Low Part): " << mAdapterDesc.AdapterLuid.LowPart << std::endl;
		log << "\tTe support per Directx 11? ";

		if (dxgiAdapter->CheckInterfaceSupport(__uuidof(ID3D10Device),NULL) == S_OK)
		{
			log << " Si" << std::endl;
		}
		else
		{
			log << " No" << std::endl;
		}

		indexOutput = 0;
		log << "\t\t===== Sortides Adaptador Numero " << indexAdapter << " =====" << std::endl;
		outputNum = 0;
		while (dxgiAdapter->EnumOutputs(indexOutput,&dxgiOutput) != DXGI_ERROR_NOT_FOUND)
		{
			dxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,DXGI_ENUM_MODES_INTERLACED,&outputNum,NULL);
			DXGI_MODE_DESC *outputModeDesc = new DXGI_MODE_DESC[outputNum];
			dxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,DXGI_ENUM_MODES_INTERLACED,&outputNum,outputModeDesc);

			for (UINT i = 0; i < outputNum; i++)
			{
				log << "\t\tAmplada: " << outputModeDesc[i].Width << " Altura: " << outputModeDesc[i].Height << " REFRESH: " <<
					outputModeDesc[i].RefreshRate.Numerator << " / " << outputModeDesc[i].RefreshRate.Denominator << std::endl;
			}

			log << "\tNumero de sortides: " << std::endl;
			
			indexOutput++;
		}
		log << "\t\t===== Fi Sortirdes Adaptador Numero " << indexAdapter << " =====" << std::endl;
		log << "\tNumero de sortides: " << indexOutput << std::endl;
		log << "\t\t===== Fi Adaptador Numero " << indexAdapter << " =====" << std::endl;

		indexAdapter++;				
	}
	log << "Total chips gràfics: " << indexAdapter << std::endl;
	log.close();

	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiOutput);
}

void DX11::onResize()
{
	assert(m_immediateContext);
	assert(m_device);
	assert(m_swapChain);

	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.

	ReleaseCOM(m_renderTargetView);
	ReleaseCOM(m_depthStencilView);
	ReleaseCOM(m_depthStencilBuffer);
	
	// Resize the swap chain and recreate the render target view.

	HR(m_swapChain->ResizeBuffers(1, m_window->getWidth(), m_window->getHeight(), DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer;
	HR(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(m_device->CreateRenderTargetView(backBuffer, 0, &m_renderTargetView));
	ReleaseCOM(backBuffer);
	
	// Create the depth/stencil buffer and view.

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	
	depthStencilDesc.Width     = m_window->getWidth();
	depthStencilDesc.Height    = m_window->getHeight();
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;

	if (m_enable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count   = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags      = 0;

	HR(m_device->CreateTexture2D(&depthStencilDesc, 0, &m_depthStencilBuffer));
	HR(m_device->CreateDepthStencilView(m_depthStencilBuffer, 0, &m_depthStencilView));
	
	// Bind the render target view and depth/stencil view to the pipeline.

	m_immediateContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
	
	// Set the viewport transform.
	
	float windowWidth = m_window->getWidth();
	float windowHeight = m_window->getHeight();
		
	m_screenViewport.TopLeftX = 0;
	m_screenViewport.TopLeftY = 0;
	m_screenViewport.Width    = static_cast<float>(windowWidth);
	m_screenViewport.Height   = static_cast<float>(windowHeight);
	m_screenViewport.MinDepth = 0.0f;
	m_screenViewport.MaxDepth = 1.0f;

	m_immediateContext->RSSetViewports(1, &m_screenViewport);

	m_camera.SetLens(0.25f*MathHelper::Pi, windowWidth / windowHeight, 1.0f, 1000.0f);
	m_camera.UpdateViewMatrix();
}

void DX11::updateScene(float delta)
{
	static int frameCnt = 0;
	static float t_base = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if( (m_window->getGameTimer()->getGameTime() - t_base) >= 1.0f )
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::wostringstream outs;   
		outs.precision(6);
		outs << m_window->getTitle() <<  L" - FPS: " << fps
			<<  " | Milliseconds: " << mspf;
		SetWindowText(m_window->getWindowHandle(), outs.str().c_str());
		
		// Reset for next average.
		frameCnt = 0;
		t_base  += 1.0f;
	}
}

void DX11::drawScene()
{
	m_immediateContext->ClearRenderTargetView(m_renderTargetView, reinterpret_cast<const float*>(&m_backgroundColor));
	m_immediateContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//------------------------------------------------------------------------------

	float gameTime = m_window->getGameTimer()->getGameTime();
	// Circle light over the land surface.
	mPointLight.Position.x = 15.0f*cosf( 0.2f* gameTime);
	mPointLight.Position.z = 15.0f*sinf( 0.2f* gameTime );
	mPointLight.Position.y = 7.0f;


	// The spotlight takes on the camera position and is aimed in the
	// same direction the camera is looking.  In this way, it looks
	// like we are holding a flashlight.
	XMStoreFloat3(&mSpotLight.Position, m_camera.GetPosition());
	XMStoreFloat3(&mSpotLight.Direction, XMVector3Normalize(m_camera.GetLook() - m_camera.GetPosition()));

	//------------------------------------------------------------------------------
	
	std::list<Dementia::Node*>* nodes = m_window->getSceneManager()->getAllNodes();
	
	Dementia::Geometry* geometry;

	XMMATRIX I = XMMatrixIdentity();

	XMMATRIX cView = m_camera.View();
	XMMATRIX cProj = m_camera.Proj();

	XMMATRIX mtView = XMMatrixTranspose(cView);
	XMMATRIX mtProj = XMMatrixTranspose(cProj); 

	for(auto dm : *nodes)
	{
		Dementia::Entity* entity = dm->getEntity();

		if (entity != nullptr)
		{

			XMMATRIX world =  dm->getWorldMatrix();

			m_cb.mWorld = dm->getWorldMatrix(); //* rotacion;
			m_cb.mView =	mtView;
			m_cb.mProjection = mtProj;
			m_cb.gDirLight = mDirLight;
			m_cb.gSpotLight = mSpotLight;
			m_cb.gPointLight = mPointLight;
			m_cb.gMaterial = mWavesMat;
			XMStoreFloat3(&m_cb.gEyePosW, m_camera.GetPosition());

			m_immediateContext->UpdateSubresource(m_defaultShader.dx_constantBuffer, 0, NULL, &m_cb, 0, 0);

			m_immediateContext->VSSetShader(m_defaultShader.g_pVertexShader, NULL, 0);
			m_immediateContext->VSSetConstantBuffers( 0, 1, &m_defaultShader.dx_constantBuffer );
			
			m_immediateContext->UpdateSubresource(m_defaultShader.dx_constantBuffer, 0, NULL, &m_cb, 0, 0);
			
			m_immediateContext->PSSetShader(m_defaultShader.g_pPixelShader, NULL, 0);
			m_immediateContext->PSSetConstantBuffers( 0, 1, &m_defaultShader.dx_constantBuffer );
			m_immediateContext->PSSetSamplers(0, 1, &m_defaultSamplerState);

			if(entity->getType() == Entity::TYPE::Light)
			{

			}
			else
			{
				Dementia::Mesh* mesh = static_cast<Mesh*>(entity);
				geometry = mesh->getGeometry();

				m_immediateContext->PSSetShaderResources( 0, 1, &mesh->getTexture()->g_pTextureRV );
				
				m_immediateContext->IASetVertexBuffers(0, 1, &geometry->vb, &stride, &offset);
				m_immediateContext->IASetIndexBuffer(geometry->ib , DXGI_FORMAT_R32_UINT, 0);
				m_immediateContext->DrawIndexed(geometry->Indices.size(), 0, 0);
			}
		}
		
	}

	HR(m_swapChain->Present(m_window->isVsync(),0));

}

HRESULT CompileShaderFromFile(const wchar_t* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);



    if( FAILED(hr) )
    {
        if( pErrorBlob != NULL )
		{
            OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
			std::cout << "Error: " << (char*)pErrorBlob->GetBufferPointer();
			MessageBoxA(NULL, (char*)pErrorBlob->GetBufferPointer(), "Error al compilar el shader", MB_OK); 
		}
        if( pErrorBlob ) pErrorBlob->Release();
        return hr;
    }
    if( pErrorBlob ) pErrorBlob->Release();

    return S_OK;
}

void DX11::BuildSamplerDesc()
{
	D3D11_SAMPLER_DESC sd;
	sd.Filter = D3D11_FILTER_ANISOTROPIC;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.MipLODBias = 0;
	sd.MaxAnisotropy = 4;
	sd.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sd.BorderColor[0] = 0;
	sd.BorderColor[1] = 0;
	sd.BorderColor[2] = 0;
	sd.BorderColor[3] = 0;
	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;

	m_device->CreateSamplerState(&sd, &m_defaultSamplerState);
}

HRESULT DX11::BuildShader(std::wstring path, Shader* shaderOutput)
{
	ID3D11Device* gDevice = m_device;

	HRESULT hr = 0;
	// Compile the vertex shader
    ID3DBlob* pVSBlob = NULL;
    hr = CompileShaderFromFile( path.c_str(), "VS", "vs_4_0", &pVSBlob );
	
    if( FAILED( hr ) )
    {
        MessageBox( NULL,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return hr;
    }

	// Create the vertex shader
	hr = gDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &shaderOutput->g_pVertexShader );
	if( FAILED( hr ) )
	{	
		pVSBlob->Release();
        return hr;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",	 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TANGENTU", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	
	
	hr = gDevice->CreateInputLayout( layout, 4, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &shaderOutput->g_pVertexLayout );

	pVSBlob->Release();
	if( FAILED( hr ) )
        return hr;

	//-----------------------------------------------------------------------

	// Compile the pixel shader
	ID3DBlob* pPSBlob = NULL;
    hr = CompileShaderFromFile( path.c_str(), "PS", "ps_4_0", &pPSBlob );
    if( FAILED( hr ) )
    {
        MessageBox( NULL,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return hr;
    }

	// Create the pixel shader
	hr = gDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &shaderOutput->g_pPixelShader );
	pPSBlob->Release();
    if( FAILED( hr ) )
        return hr;

	//--------------------------------------------------------------------------
	// Create the constant buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
    hr = m_device->CreateBuffer( &bd, NULL, &shaderOutput->dx_constantBuffer );
    if( FAILED( hr ) )
        return hr;

	return S_OK;
}


}