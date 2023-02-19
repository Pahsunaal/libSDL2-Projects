#ifndef M2D_KEYBOARD_IO_IH
#define M2D_KEYBOARD_IO_IH

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DKeyboardIO.h"

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace IO
{

class KeyboardInputImp : public KeyboardInput
{
public:
	KeyboardInputImp();
	~KeyboardInputImp();

	// Interface

	bool GetKeyDown(int key_scancode);
	bool GetKeyUp(int key_scancode);
	bool GetKey(int key_scancode);

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

}

#endif // M2D_KEYBOARD_IO_IH