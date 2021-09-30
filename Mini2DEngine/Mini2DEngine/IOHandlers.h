#pragma once
#include <SDL.h>

namespace IO {
	struct MouseInput {
		MouseInput();
		bool getLeftButtonDown();
		bool getRightButtonDown();
		bool getLeftButtonUp();
		bool getRightButtonUp();
		bool getLeftButton();
		bool getRightButton();
		int getX();
		int getY();
		void setLeftButtonDown(bool down);
		void setRightButtonDown(bool down);
		void setLeftButtonUp(bool Up);
		void setRightButtonUp(bool Up);
		void setLeftButton(bool held);
		void setRightButton(bool held);
		void setX(int newx);
		void setY(int newy);
		void endUpdate();
	private:
		int x;
		int y;
		bool leftButton[3];
		bool rightButton[3];
	};

	struct KeyboardInput {
		KeyboardInput();
		~KeyboardInput();
		bool getKeyDown(int key_scancode);
		bool getKeyUp(int key_scancode);
		bool getKey(int key_scancode);
		void setKeyDown(int key_scancode, bool down);
		void setKeyUp(int key_scancode, bool up);
		void endUpdate();
	private:
		const Uint8* keys;
		int numKeys;
		bool* keysDown;
		bool* keysUp;
	};
}