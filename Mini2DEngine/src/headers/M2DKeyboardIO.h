#ifndef M2D_KEYBOARD_IO_IH
#define M2D_KEYBOARD_IO_IH

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DKeyboardIO.h"

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

class KeyboardInputImp : public KeyboardInput
{
	KeyboardInputImp();
	~KeyboardInputImp();

	// Interface

	bool GetKeyDown(int key_scancode) override;
	bool GetKeyUp(int key_scancode) override;
	bool GetKey(int key_scancode) override;

	// Engine

	void SetKeyDown(int key_scancode, bool down);
	void SetKeyUp(int key_scancode, bool up);
	void EndUpdate();
private:
	const Uint8* keys;
	int numKeys;
	bool* keysDown;
	bool* keysUp;
};

#endif // M2D_KEYBOARD_IO_IH