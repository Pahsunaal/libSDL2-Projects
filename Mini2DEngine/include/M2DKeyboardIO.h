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
	KeyboardInput(){};

	/** Destroy KeyboardInput object */
	~KeyboardInput(){};

	/** Check if key pressed 
	* @param key_scancode: the code of the key to check. Refer to SDL Scancodes online
	*/
	virtual bool GetKeyDown(int key_scancode) = 0;

	/** Check if key released
	* @param key_scancode: the code of the key to check. Refer to SDL Scancodes online
	*/
	virtual bool GetKeyUp(int key_scancode) = 0;

	/** Check state of key
	* @param key_scancode: the code of the key to check. Refer to SDL Scancodes online
	*/
	virtual bool GetKey(int key_scancode) = 0;
};

}

#endif // M2D_KEYBOARD_IO_H