#pragma once

/**
* @file GameText.h
* @brief Handle text objects
***************************************************/

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace GameText {
	/** Maximum number of text objects the engine allows */
	const size_t max_texts{ 100 };

	/** A Text object - when initialised and drawn, will display its contained message with a defined colour and size */
	struct Text {
		/**
		* Construct new Text object - use TextManager.createText() for safer text object creation
		* 
		* @param fontpath: the path to the ttf font file
		* @param size: the size of the font in pixels
		* @param message: the c-string message to display
		* @param color: the color of the text
		* @param renderer: the SDL_Renderer to use, as a pointer
		* @param index: the index of the text object in the text array
		*/
		Text(const char* fontpath, int size, const char* message, SDL_Color color, SDL_Renderer* renderer, size_t index);

		/**
		* Construct new Text object - use TextManager.createText() for safer text object creation
		*
		* @param fontpath: the path to the ttf font file
		* @param size: the size of the font in pixels
		* @param message: the c-string message to display
		* @param color: the color of the text
		* @param renderer: the SDL_Renderer to use, as a pointer
		* @param width: the width of the text area
		* @param height: the height of the text area
		* @param index: the index of the text object in the text array
		*/
		Text(const char* fontpath, int size, const char* message, SDL_Color color, SDL_Renderer* renderer, int width, int height, size_t index);

		/** Destroy the Text object - use TextManager.destroyText() for safer text object destruction */
		~Text();

		/**
		* Draw the text object at the given x and y
		*
		* @param newx: the x coordinate to draw at
		* @param newy: the y coordinate to draw at
		*/
		void draw(double newx, double newy);

		/**
		* Draw the text object at the given x and y, at an angle
		*
		* @param newx: the x coordinate to draw at
		* @param newy: the y coordinate to draw at
		* @param angle: the angle to draw the text at
		*/
		void draw(double newx, double newy, double angle);

		/**
		* Draw the text object at the given x and y, at an angle, with a new message. Can automatically determine new size based on message, or simply keep the old size
		*
		* @param newx: the x coordinate to draw at
		* @param newy: the y coordinate to draw at
		* @param angle: the angle to draw the text at
		* @param newmessage: the new cstring to display
		* @param autoSize: whether to automatically resize text area to contain new message, or keep old size
		*/
		void drawExt(double newx, double newy, double angle, const char* newmessage, bool autoSize);

		/**
		* Change the text cstring to display
		*
		* @param newmessage: the new cstring to display
		* @param autoSize: whether to automatically resize text area to contain new message, or keep old size
		*/
		void changeMessage(const char* newmessage, bool autoSize);

		/**
		* Change angle of text object
		*
		* @param angle: the angle to draw the text at
		*/
		void setAngle(double newangle);

		/** Get the angle of the text object */
		double getAngle();

		/** A Text objects index position in the text_array of TextManager */
		size_t index;
	private:
		SDL_Texture* texture;
		SDL_Surface* temp;
		SDL_Renderer* renderer;
		TTF_Font* font;
		SDL_Rect rect;
		SDL_Color color;
		std::string message;
		int width;
		int height;
		int size;
		double angle;
	};

	/** Manage the lifetime and storage of Text objects */
	struct TextManager {
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