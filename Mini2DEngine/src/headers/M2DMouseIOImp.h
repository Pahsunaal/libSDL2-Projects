#ifndef M2D_MOUSE_IO_IH
#define M2D_MOUSE_IO_IH

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DMouseIO.h"

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace IO
{

class MouseInputImp : public MouseInput
{
public:
	MouseInputImp();

	// Interface

	bool GetLeftButtonDown();
	bool GetRightButtonDown();
	bool GetLeftButtonUp();
	bool GetRightButtonUp();
	bool GetLeftButton();
	bool GetRightButton();
	int GetX();
	int GetY();

	// Engine

	void SetLeftButtonDown(bool down);
	void SetRightButtonDown(bool down);
	void SetLeftButtonUp(bool Up);
	void SetRightButtonUp(bool Up);
	void SetLeftButton(bool held);
	void SetRightButton(bool held);
	void SetX(int newx);
	void SetY(int newy);
	void EndUpdate();
private:
	int x;
	int y;
	bool leftButton[3];
	bool rightButton[3];
};

}

#endif // M2D_MOUSE_IO_IH