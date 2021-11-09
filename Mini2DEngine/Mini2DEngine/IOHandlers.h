#pragma once

/**
* @file IOHandlers.h
* @brief Handle the keyboard and mouse IO, connecting user-defined code to SDL events
***************************************************/

#include <SDL.h>

namespace IO {
	/** Handle mouse input */
	struct MouseInput {
		/** Construct new MouseInput object*/
		MouseInput();

		/** Check if left mouse button pressed */
		bool getLeftButtonDown();

		/** Check if right mouse button pressed */
		bool getRightButtonDown();

		/** Check if left mouse button released */
		bool getLeftButtonUp();

		/** Check if right mouse button released */
		bool getRightButtonUp();

		/** Check state of left mouse button */
		bool getLeftButton();

		/** Check state of left mouse button */
		bool getRightButton();

		/** Get x position of mouse in room */
		int getX();

		/** Get y position of mouse in room */
		int getY();

		/* Following functions are engine ONLY - used to set values */

		/** Engine utility function, do not use */
		void setLeftButtonDown(bool down);

		/** Engine utility function, do not use */
		void setRightButtonDown(bool down);

		/** Engine utility function, do not use */
		void setLeftButtonUp(bool Up);

		/** Engine utility function, do not use */
		void setRightButtonUp(bool Up);

		/** Engine utility function, do not use */
		void setLeftButton(bool held);
		
		/** Engine utility function, do not use */
		void setRightButton(bool held);

		/** Engine utility function, do not use */
		void setX(int newx);

		/** Engine utility function, do not use */
		void setY(int newy);

		/** Engine utility function, do not use */
		void endUpdate();
	private:
		int x;
		int y;
		bool leftButton[3];
		bool rightButton[3];
	};

	struct KeyboardInput {
		/** Construct new KeyboardInput object */
		KeyboardInput();

		/** Destroy KeyboardInput object */
		~KeyboardInput();

		/** Check if key pressed 
		* @param key_scancode: the code of the key to check. Refer to SDL Scancodes online
		*/
		bool getKeyDown(int key_scancode);

		/** Check if key released
		* @param key_scancode: the code of the key to check. Refer to SDL Scancodes online
		*/
		bool getKeyUp(int key_scancode);

		/** Check state of key
		* @param key_scancode: the code of the key to check. Refer to SDL Scancodes online
		*/
		bool getKey(int key_scancode);

		/** Engine utility function, do not use */
		void setKeyDown(int key_scancode, bool down);

		/** Engine utility function, do not use */
		void setKeyUp(int key_scancode, bool up);

		/** Engine utility function, do not use */
		void endUpdate();
	private:
		const Uint8* keys;
		int numKeys;
		bool* keysDown;
		bool* keysUp;
	};
}