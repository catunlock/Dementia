#include "InputManager.h"

namespace Dementia{

	InputManager::InputManager() :
		mouse(0,0)
	{
	}


	InputManager::~InputManager(void)
	{
	}

	void InputManager::processEvent(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch(msg){
		case WM_LBUTTONDOWN:
			mouse.setButtonPressed(Mouse::Button::Left, XMFLOAT2(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
			return;
		case WM_MBUTTONDOWN:
			mouse.setButtonPressed(Mouse::Button::Middle, XMFLOAT2(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
			return;
		case WM_RBUTTONDOWN:
			mouse.setButtonPressed(Mouse::Button::Right, XMFLOAT2(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
			return;
		case WM_LBUTTONUP:
			mouse.setButtonReleased(Mouse::Button::Left, XMFLOAT2(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));		
			return;
		case WM_MBUTTONUP:
			mouse.setButtonReleased(Mouse::Button::Middle, XMFLOAT2(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
			return;
		case WM_RBUTTONUP:
			mouse.setButtonReleased(Mouse::Button::Right, XMFLOAT2(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
			return;
		case WM_MOUSEMOVE:
			mouse.updatePosition(XMFLOAT2(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
			return;

		case WM_KEYDOWN:
			keyboard.setKeyPressed(wParam);
			return;
		case WM_KEYUP:
			keyboard.setKeyReleased(wParam);
			return;
		}
	}

}