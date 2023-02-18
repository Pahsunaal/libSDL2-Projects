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

}

#endif // M2D_MOUSE_IO_H