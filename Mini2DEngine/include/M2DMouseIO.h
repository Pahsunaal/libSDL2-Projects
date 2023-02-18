#ifndef M2D_MOUSE_IO_H
#define M2D_MOUSE_IO_H

/**
* @file M2DMouseIO.h
* @brief Handle the mouse IO, connecting user-defined code to SDL events
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

/** Handle mouse input */
class MouseInput
{
public:
	/** Construct new MouseInput object*/
	MouseInput(){};

	/** Check if left mouse button pressed */
	virtual bool GetLeftButtonDown() = 0;

	/** Check if right mouse button pressed */
	virtual bool GetRightButtonDown() = 0;

	/** Check if left mouse button released */
	virtual bool GetLeftButtonUp() = 0;

	/** Check if right mouse button released */
	virtual bool GetRightButtonUp() = 0;

	/** Check state of left mouse button */
	virtual bool GetLeftButton() = 0;

	/** Check state of left mouse button */
	virtual bool GetRightButton() = 0;

	/** Get x position of mouse in room */
	virtual int GetX() = 0;

	/** Get y position of mouse in room */
	virtual int GetY() = 0;
};

}

#endif // M2D_MOUSE_IO_H