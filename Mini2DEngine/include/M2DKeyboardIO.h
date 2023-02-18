#ifndef M2D_KEYBOARD_IO_H
#define M2D_KEYBOARD_IO_H

/**
* @file M2DKeyboardIO.h
* @brief Handle the keyboard IO, connecting user-defined code to SDL events
***************************************************/

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include <SDL.h>

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace IO
{

/** Handle keyboard input */
class KeyboardInput
{
public:
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

#endif // M2D_KEYBOARD_IO_H