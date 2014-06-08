#include "Window.h"

namespace Dementia
{
	LRESULT CALLBACK
	MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		static Window* window = 0;

		switch( msg )
		{
			case WM_CREATE:
			{
				// Get the 'this' pointer we passed to CreateWindow via the lpParam parameter.
				CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
				window = (Window*)cs->lpCreateParams;
				return 0;
			}
		}

		// Don't start processing messages until after WM_CREATE.
		if( window )
		{
			return window->msgProc(msg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}

	Window::Window(UINT id, UINT width, UINT height, std::wstring title, bool vsync, bool windowed) :
		m_id(id),
		m_width(width),
		m_height(height),
		m_title(title),
		m_vsync(vsync),
		m_windowed(windowed),
		m_appPaused(false), 
		m_Minimized(false), 
		m_Maximized(false), 
		m_resizing(false),
		m_init(false),
		m_hWindow(0),
		m_hInstance(GetModuleHandle(NULL))
	{
		m_timer.reset();
	}

	void Window::init()
	{
		initWindow();
		m_dx11 = new Dementia::DX11(this);
		m_sceneManager = new Dementia::SceneManager(this);

		m_init = true;
	}

	Window::~Window(void)
	{
		release();
	}

	void Window::release()
	{
		DestroyWindow(m_hWindow);
		delete m_dx11;
		delete m_sceneManager;
	}
	
	HWND Window::initWindow()
	{
		WNDCLASS wc;
		wc.style         = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc   = MainWndProc; 
		wc.cbClsExtra    = 0;
		wc.cbWndExtra    = 0;
		wc.hInstance     = m_hInstance;
		wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
		wc.hCursor       = LoadCursor(0, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
		wc.lpszMenuName  = 0;
		wc.lpszClassName = m_title.c_str();

		if( !RegisterClass(&wc) )
		{
			MessageBox(0, L"RegisterClass FAILED", 0, 0);
			PostQuitMessage(0);
		}

		// Compute window rectangle dimensions based on requested client area dimensions.
		RECT R = { 0, 0, m_width, m_height };
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
		int width  = R.right - R.left;
		int height = R.bottom - R.top;

		m_hWindow = CreateWindow(m_title.c_str(), m_title.c_str(), 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height, 0, 0, m_hInstance, this);

		if( !m_hWindow )
		{
			showErrorMessage(GetLastError());
			PostQuitMessage(0);
		}

		ShowWindow(m_hWindow, SW_SHOW);
		UpdateWindow(m_hWindow);
		//ShowCursor(false);
		SetCapture(m_hWindow);
		return m_hWindow;
	}

	bool Window::run(int* exitCode)
	{
		MSG msg = {0};

		if(PeekMessage(&msg, 0,0,0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			m_timer.tick();

			if( !m_appPaused )
			{
				m_dx11->updateScene(m_timer.getDeltaTime());
				m_dx11->drawScene();
			}
			else
			{
				Sleep(50);
			}			
		}
	
		if(msg.message == WM_QUIT )
		{
			if(exitCode != nullptr)
			{
				*exitCode = (int)msg.wParam; 
			}

			return false;
		}

		return true;
	}

	LRESULT Window::msgProc(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch( msg )
		{
		// WM_ACTIVATE is sent when the window is activated or deactivated.  
		// We pause the game when the window is deactivated and unpause it 
		// when it becomes active.  
		case WM_ACTIVATE:
			if( LOWORD(wParam) == WA_INACTIVE )
			{
				m_appPaused = true;
				m_timer.stop();
			}
			else
			{
				m_appPaused = false;
				m_timer.start();
			}
			return 0;

		// WM_SIZE is sent when the user resizes the window.  
		case WM_SIZE:
		
			// Save the new client area dimensions.
			m_width  = LOWORD(lParam);
			m_height = HIWORD(lParam);
			if(m_init)  //Pregunta si se ha inicializado correctamente el clase dx11.
			{
				if( wParam == SIZE_MINIMIZED )
				{
					m_appPaused = true;
					m_Minimized = true;
					m_Maximized = false;
				}
				else if( wParam == SIZE_MAXIMIZED )
				{
					m_appPaused = false;
					m_Minimized = false;
					m_Maximized = true;
					m_dx11->onResize();
				}
				else if( wParam == SIZE_RESTORED )
				{
					// Restoring from minimized state?
					if( m_Minimized )
					{
						m_appPaused = false;
						m_Minimized = false;
						m_dx11->onResize();
					}
				
					// Restoring from maximized state?
					else if( m_Maximized )
					{
						m_appPaused = false;
						m_Maximized = false;
						m_dx11->onResize();
					}
					else if( m_resizing )
					{
						// If user is dragging the resize bars, we do not resize 
						// the buffers here because as the user continuously 
						// drags the resize bars, a stream of WM_SIZE messages are
						// sent to the window, and it would be pointless (and slow)
						// to resize for each WM_SIZE message received from dragging
						// the resize bars.  So instead, we reset after the user is 
						// done resizing the window and releases the resize bars, which 
						// sends a WM_EXITSIZEMOVE message.
					}
					else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
					{
						m_dx11->onResize();
					}
				
				}
			}
		
			return 0;

		// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
		case WM_ENTERSIZEMOVE:
		
			m_appPaused = true;
			m_resizing  = true;
			m_timer.stop();
		
			return 0;

		// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
		// Here we reset everything based on the new window dimensions.
		case WM_EXITSIZEMOVE:
		
			m_appPaused = false;
			m_resizing  = false;
			m_timer.start();
			m_dx11->onResize();
		
			return 0;
 
		// WM_DESTROY is sent when the window is being destroyed.
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		// The WM_MENUCHAR message is sent when a menu is active and the user presses 
		// a key that does not correspond to any mnemonic or accelerator key. 
		case WM_MENUCHAR:
			// Don't beep when we alt-enter.
			return MAKELRESULT(0, MNC_CLOSE);

		// Catch this message so to prevent the window from becoming too small.
		case WM_GETMINMAXINFO:
			((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
			((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200; 
			return 0;
	
		default:
			m_inputManager.processEvent(msg, wParam, lParam);
		}
	
		return DefWindowProc(m_hWindow, msg, wParam, lParam);
	}

	void Window::setBackgroundColor(XMVECTOR backgroundColor)
	{
		m_dx11->setBackgroundColor(backgroundColor); 
	}

	XMVECTOR Window::getBackgroundColor()
	{ 
		return m_dx11->getBackgroundColor(); 
	}

	ID3D11Device* Window::getDevice()
	{ 
		return m_dx11->getDevice();
	}

	Dementia::Camera* Window::getCamera() 
	{ 
		return m_dx11->getCamera(); 
	};

	Dementia::SceneManager* Window::getSceneManager()
	{ 
		return m_sceneManager; 
	};
}
