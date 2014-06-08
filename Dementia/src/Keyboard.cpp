#include "Keyboard.h"

namespace Dementia
{

Keyboard::Keyboard(void)
{
	ZeroMemory(keysPressed, sizeof(keysPressed) );
}


Keyboard::~Keyboard(void)
{
}

void Keyboard::setKeyPressed(int key)
{
	keysPressed[key] = true;
}
void Keyboard::setKeyReleased(int key)
{
	keysPressed[key] = false;
}

bool Keyboard::isKeyPressed(int key)
{
	return keysPressed[key];
}

}