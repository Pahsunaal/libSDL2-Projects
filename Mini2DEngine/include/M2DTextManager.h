#pragma once

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
//  Class Declaration
//--------------------------------------------------

namespace Text {
/** Maximum number of text objects the engine allows */
const size_t max_texts{ 100 };

/** Manage the lifetime and storage of Text objects */
class TextManager {
public:
	/**
	* Construct a new TextManager
	* @param renderer: pointer to the SDL_Renderer target to use
	*/
	TextManager(SDL_Renderer* renderer);
	/** Destructs the TextManager */
	~TextManager();

	/**
	* Construct new Text object safely
	*
	* @param fontpath: the path to the ttf font file
	* @param size: the size of the font in pixels
	* @param message: the c-string message to display
	* @param color: the color of the text
	*/
	Text* createText(const char* fontpath, int size, const char* message, SDL_Color color);

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
	Text* createText(const char* fontpath, int size, const char* message, SDL_Color color, int width, int height);

	/** Destroy the referenced Text object 
	* @param text: pointer to the Text object to destroy
	*/
	void destroyText(Text* text);

private:
	Text* text_array[max_texts];
	size_t num_texts;
	SDL_Renderer* renderer;
};
}