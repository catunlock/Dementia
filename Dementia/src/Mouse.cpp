#include "Mouse.h"

namespace Dementia
{

Mouse::Mouse(void) :
	position(0,0),
	moved(false)
{
	ZeroMemory(&pressedButtons, sizeof(pressedButtons));
}

Mouse::Mouse(float x, float y) :
	position(x,y),
	moved(false)
{
	ZeroMemory(&pressedButtons, sizeof(pressedButtons));
}

Mouse::~Mouse(void)
{
}

void Mouse::setButtonPressed(Button buttonPressed, XMFLOAT2 newPosition)
{
	pressedButtons[buttonPressed] = true;
	position = newPosition;
}

void Mouse::setButtonReleased(Button buttonPressed, XMFLOAT2 newPosition)
{
	pressedButtons[buttonPressed] = false;
	position = newPosition;
}

bool Mouse::isButtonPressed(Button button)
{
	return pressedButtons[button];
}

bool Mouse::isMoved()
{
	return moved;
}

void Mouse::updatePosition(XMFLOAT2 newPosition)
{
	moved = true;
	if(position.x  != newPosition.x || position.y != newPosition.y){

		position.x = newPosition.x;
		position.y = newPosition.y;
		//setPosition(m_center);
	}
}

void Mouse::setCenter(XMFLOAT2 center)
{
	m_center.x = center.x;
	m_center.y = center.y;
}

void Mouse::setPosition(XMFLOAT2 newPosition)
{
	SetCursorPos(m_center.x, m_center.y);
}

XMFLOAT2 Mouse::getPosition()
{
	moved = false;
	return position;
}

}