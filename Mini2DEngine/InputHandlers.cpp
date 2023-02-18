#include "IOHandlers.h"
#include <SDL.h>
#include <cstdio>

using namespace IO;

#pragma region Mouse

MouseInput::MouseInput() : x{}, y{}, leftButton{ false,false,false }, rightButton{ false,false,false } {
}

bool MouseInput::getLeftButtonDown() {
	return leftButton[0];
}

bool MouseInput::getRightButtonDown() {
	return rightButton[0];
}

bool MouseInput::getLeftButtonUp() {
	return leftButton[1];
}

bool MouseInput::getRightButtonUp() {
	return rightButton[1];
}

bool MouseInput::getLeftButton() {
	return leftButton[2];
}

bool MouseInput::getRightButton() {
	return rightButton[2];
}

int MouseInput::getX() {
	return x;
}

int MouseInput::getY() {
	return y;
}

void MouseInput::setLeftButtonDown(bool down) {
	leftButton[0] = down;
	if (down) {
		leftButton[2] = true;
	}
}

void MouseInput::setRightButtonDown(bool down) {
	rightButton[0] = down;
	if (down) {
		rightButton[2] = true;
	}
}

void MouseInput::setLeftButtonUp(bool up) {
	leftButton[1] = up;
	if (up) {
		leftButton[2] = false;
	}
}

void MouseInput::setRightButtonUp(bool up) {
	rightButton[1] = up;
	if (up) {
		rightButton[2] = false;
	}
}

void MouseInput::setLeftButton(bool held) {
	leftButton[2] = held;
}

void MouseInput::setRightButton(bool held) {
	rightButton[2] = held;
}

void MouseInput::setX(int newx) {
	x = newx;
}

void MouseInput::setY(int newy) {
	y = newy;
}

void MouseInput::endUpdate() {
	// For single click checks
	MouseInput::setLeftButtonDown(false);
	MouseInput::setLeftButtonUp(false);
	MouseInput::setRightButtonDown(false);
	MouseInput::setRightButtonUp(false);
}

#pragma endregion

#pragma region Keyboard

KeyboardInput::KeyboardInput() : numKeys{} {
	keys = SDL_GetKeyboardState(&numKeys);
	keysDown = new bool[numKeys] {};
	keysUp = new bool[numKeys] {};
}

KeyboardInput::~KeyboardInput() {
	delete[] keysDown;
	delete[] keysUp;
}

bool KeyboardInput::getKeyDown(int key_scancode) {
	if(key_scancode < numKeys) return keysDown[key_scancode];
	return false;
}

bool KeyboardInput::getKeyUp(int key_scancode) {
	if (key_scancode < numKeys) return keysUp[key_scancode];
	return false;
}

bool KeyboardInput::getKey(int key_scancode) {
	if (key_scancode < numKeys) return keys[key_scancode];
	return false;
}

void KeyboardInput::setKeyDown(int key_scancode, bool down) {
	if (key_scancode < numKeys) keysDown[key_scancode] = down;
}

void KeyboardInput::setKeyUp(int key_scancode, bool up) {
	if (key_scancode < numKeys) keysUp[key_scancode] = up;
}

void KeyboardInput::endUpdate() {
	keys = SDL_GetKeyboardState(&numKeys);
	for (int i{}; i < numKeys; i++) {
		// For single press checks
		keysDown[i] = false;
		keysUp[i] = false;
	}
}

#pragma endregion