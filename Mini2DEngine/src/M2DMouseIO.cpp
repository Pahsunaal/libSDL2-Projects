//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DMouseIOImp.h"
#include <SDL.h>
#include <cstdio>

//--------------------------------------------------
//  Types
//--------------------------------------------------

using namespace IO;


//--------------------------------------------------
//  MouseInput::Get() : .
//--------------------------------------------------
MouseInput* MouseInput::Get()
{
	static MouseInputImp mouseInput;
	return static_cast<MouseInput*>(&mouseInput);
}





//--------------------------------------------------
//  MouseInputImp::MouseInputImp() : .
//--------------------------------------------------
MouseInputImp::MouseInputImp() : x{},
						   y{},
						   leftButton{ false,false,false },
						   rightButton{ false,false,false }
{
}





//--------------------------------------------------
//  MouseInputImp::GetLeftButtonDown() : .
//--------------------------------------------------
bool MouseInputImp::GetLeftButtonDown()
{
	return leftButton[0];
}





//--------------------------------------------------
//  MouseInputImp::GetRightButtonDown() : .
//--------------------------------------------------
bool MouseInputImp::GetRightButtonDown()
{
	return rightButton[0];
}





//--------------------------------------------------
//  MouseInputImp::GetLeftButtonUp() : .
//--------------------------------------------------
bool MouseInputImp::GetLeftButtonUp()
{
	return leftButton[1];
}





//--------------------------------------------------
//  MouseInputImp::GetRightButtonUp() : .
//--------------------------------------------------
bool MouseInputImp::GetRightButtonUp()
{
	return rightButton[1];
}





//--------------------------------------------------
//  MouseInputImp::GetLeftButton() : .
//--------------------------------------------------
bool MouseInputImp::GetLeftButton()
{
	return leftButton[2];
}





//--------------------------------------------------
//  MouseInputImp::GetRightButton() : .
//--------------------------------------------------
bool MouseInputImp::GetRightButton()
{
	return rightButton[2];
}





//--------------------------------------------------
//  MouseInputImp::GetX() : .
//--------------------------------------------------
int MouseInputImp::GetX()
{
	return x;
}





//--------------------------------------------------
//  MouseInputImp::GetY() : .
//--------------------------------------------------
int MouseInputImp::GetY()
{
	return y;
}





//--------------------------------------------------
//  MouseInputImp::SetLeftButtonDown() : .
//--------------------------------------------------
void MouseInputImp::SetLeftButtonDown(bool down)
{
	leftButton[0] = down;
	if (down) {
		leftButton[2] = true;
	}
}





//--------------------------------------------------
//  MouseInputImp::SetRightButtonDown() : .
//--------------------------------------------------
void MouseInputImp::SetRightButtonDown(bool down)
{
	rightButton[0] = down;
	if (down) {
		rightButton[2] = true;
	}
}





//--------------------------------------------------
//  MouseInputImp::SetLeftButtonUp() : .
//--------------------------------------------------
void MouseInputImp::SetLeftButtonUp(bool up)
{
	leftButton[1] = up;
	if (up) {
		leftButton[2] = false;
	}
}





//--------------------------------------------------
//  MouseInputImp::SetRightButtonUp() : .
//--------------------------------------------------
void MouseInputImp::SetRightButtonUp(bool up)
{
	rightButton[1] = up;
	if (up) {
		rightButton[2] = false;
	}
}





//--------------------------------------------------
//  MouseInputImp::SetLeftButton() : .
//--------------------------------------------------
void MouseInputImp::SetLeftButton(bool held)
{
	leftButton[2] = held;
}





//--------------------------------------------------
//  MouseInputImp::SetRightButton() : .
//--------------------------------------------------
void MouseInputImp::SetRightButton(bool held)
{
	rightButton[2] = held;
}





//--------------------------------------------------
//  MouseInputImp::SetX() : .
//--------------------------------------------------
void MouseInputImp::SetX(int newx)
{
	x = newx;
}





//--------------------------------------------------
//  MouseInputImp::SetY() : .
//--------------------------------------------------
void MouseInputImp::SetY(int newy)
{
	y = newy;
}





//--------------------------------------------------
//  MouseInputImp::EndUpdate() : .
//--------------------------------------------------
void MouseInputImp::EndUpdate()
{
	// For single click checks
	MouseInputImp::SetLeftButtonDown(false);
	MouseInputImp::SetLeftButtonUp(false);
	MouseInputImp::SetRightButtonDown(false);
	MouseInputImp::SetRightButtonUp(false);
}