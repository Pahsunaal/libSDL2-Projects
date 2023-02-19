#ifndef M2D_TEXT_H
#define M2D_TEXT_H

/**
* @file M2DText.h
* @brief Handle text objects
***************************************************/

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace Text {

/**
 * A Text object - when initialised and drawn, will display its contained message with a defined colour and size.
 * These should NOT be created directly. Use TextManager::createText() instead, and TextManager::destroyText()
 * for destruction.
 */
class Text {
	/**
	* Draw the text object at the given x and y
	*
	* @param newx: the x coordinate to draw at
	* @param newy: the y coordinate to draw at
	*/
	virtual void Draw(double newx, double newy) = 0;

	/**
	* Draw the text object at the given x and y, at an angle
	*
	* @param newx: the x coordinate to draw at
	* @param newy: the y coordinate to draw at
	* @param angle: the angle to draw the text at
	*/
	virtual void Draw(double newx, double newy, double angle) = 0;

	/**
	* Draw the text object at the given x and y, at an angle, with a new message. Can automatically determine new size based on message, or simply keep the old size
	*
	* @param newx: the x coordinate to draw at
	* @param newy: the y coordinate to draw at
	* @param angle: the angle to draw the text at
	* @param newmessage: the new cstring to display
	* @param autoSize: whether to automatically resize text area to contain new message, or keep old size
	*/
	virtual void DrawExt(double newx, double newy, double angle, const char* newmessage, bool autoSize) = 0;

	/**
	* Change the text cstring to display
	*
	* @param newmessage: the new cstring to display
	* @param autoSize: whether to automatically resize text area to contain new message, or keep old size
	*/
	virtual void ChangeMessage(const char* newmessage, bool autoSize) = 0;

	/**
	* Change angle of text object
	*
	* @param angle: the angle to draw the text at
	*/
	virtual void SetAngle(double newangle) = 0;

	/** Get the angle of the text object */
	virtual double GetAngle() = 0;

	/** Get the Text objects index position in the text_array of TextManager */
	virtual size_t GetIndex() = 0;
protected:
	Text(){};
	~Text(){};
};

}

#endif // M2D_TEXT_H