#ifndef M2D_TEXT_MANAGER_H
#define M2D_TEXT_MANAGER_H

/**
* @file GameText.h
* @brief Handle text objects
***************************************************/

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

//--------------------------------------------------
//  Types
//--------------------------------------------------



//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace Txt
{

class Text;
/** Maximum number of text objects the engine allows */
const size_t max_texts{ 100 };

/** Manage the lifetime and storage of Text objects */
class TextManager
{
public:
	/** Get the TextManager object */
	static TextManager* Get();

	/**
	* Construct new Text object safely
	*
	* @param fontpath: the path to the ttf font file
	* @param size: the size of the font in pixels
	* @param message: the c-string message to display
	* @param color: the color of the text
	*/
	virtual Text* CreateText(const char* fontpath, int size, const char* message, SDL_Color color) = 0;

	/**
	* Construct new Text object safely
	*
	* @param fontpath: the path to the ttf font file
	* @param size: the size of the font in pixels
	* @param message: the c-string message to display
	* @param color: the color of the text
	* @param width: the width of the text area
	* @param height: the height of the text area
	*/
	virtual Text* CreateText(const char* fontpath, int size, const char* message, SDL_Color color, int width, int height) = 0;

	/** Destroy the referenced Text object 
	* @param text: pointer to the Text object to destroy
	*/
	virtual void DestroyText(Text* text) = 0;
protected:
	TextManager(){};
	~TextManager(){};
};

}

#endif // M2D_TEXT_MANAGER_H