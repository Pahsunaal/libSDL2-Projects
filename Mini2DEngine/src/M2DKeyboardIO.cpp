//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DKeyboardIOImp.h"
#include <SDL.h>
#include <cstdio>

//--------------------------------------------------
//  Types
//--------------------------------------------------

using namespace IO;





//--------------------------------------------------
//  KeyboardInput::Get() : .
//--------------------------------------------------
KeyboardInput* KeyboardInput::Get()
{
	static KeyboardInputImp keyboardInput;
	return static_cast<KeyboardInput*>(&keyboardInput);
}





//--------------------------------------------------
//  KeyboardInputImp::KeyboardInputImp() : .
//--------------------------------------------------
KeyboardInputImp::KeyboardInputImp() : numKeys{}
{
	keys = SDL_GetKeyboardState(&numKeys);
	keysDown = new bool[numKeys] {};
	keysUp = new bool[numKeys] {};
}





//--------------------------------------------------
//  KeyboardInputImp::~KeyboardInputImp() : .
//--------------------------------------------------
KeyboardInputImp::~KeyboardInputImp()
{
	delete[] keysDown;
	delete[] keysUp;
}





//--------------------------------------------------
//  KeyboardInputImp::GetKeyDown() : .
//--------------------------------------------------
bool KeyboardInputImp::GetKeyDown(int key_scancode)
{
	if(key_scancode < numKeys) return keysDown[key_scancode];
	return false;
}





//--------------------------------------------------
//  KeyboardInputImp::GetKeyUp() : .
//--------------------------------------------------
bool KeyboardInputImp::GetKeyUp(int key_scancode)
{
	if (key_scancode < numKeys) return keysUp[key_scancode];
	return false;
}





//--------------------------------------------------
//  KeyboardInputImp::GetKey() : .
//--------------------------------------------------
bool KeyboardInputImp::GetKey(int key_scancode)
{
	if (key_scancode < numKeys) return keys[key_scancode];
	return false;
}





//--------------------------------------------------
//  KeyboardInputImp::SetKeyDown() : .
//--------------------------------------------------
void KeyboardInputImp::SetKeyDown(int key_scancode, bool down)
{
	if (key_scancode < numKeys) keysDown[key_scancode] = down;
}





//--------------------------------------------------
//  KeyboardInputImp::SetKeyUp() : .
//--------------------------------------------------
void KeyboardInputImp::SetKeyUp(int key_scancode, bool up)
{
	if (key_scancode < numKeys) keysUp[key_scancode] = up;
}





//--------------------------------------------------
//  KeyboardInputImp::EndUpdate() : .
//--------------------------------------------------
void KeyboardInputImp::EndUpdate()
{
	keys = SDL_GetKeyboardState(&numKeys);
	for (int i{}; i < numKeys; i++) {
		// For single press checks
		keysDown[i] = false;
		keysUp[i] = false;
	}
}