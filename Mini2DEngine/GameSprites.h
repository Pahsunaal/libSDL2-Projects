#pragma once

/**
* @file GameSprites.h
* @brief Handle sprites
***************************************************/

#include <SDL.h>
#include <rapidjson/document.h>

namespace GameSpr {

	/** Represents a texture to draw to the screen, storing important details about its position in-world */
	struct Sprite {
		/**
		* Construct new Sprite
		*
		* @param name: the name of the sprite
		* @param path: the path to the sprite's image file
		* @param path: the path to the sprite's properties file
		* @param renderer: the SDL_Renderer to use, as a pointer
		*/
		Sprite(const char* name, const char* path, const char* detailspath, SDL_Renderer* renderer);

		/** Destroys the sprite */
		~Sprite();

		/**
		* Draw the Sprite object at the given x and y
		*
		* @param newx: the x coordinate to draw at
		* @param newy: the y coordinate to draw at
		*/
		void draw(double newx, double newy);

		/**
		* Draw the sprite object at the given x and y, at an angle
		*
		* @param newx: the x coordinate to draw at
		* @param newy: the y coordinate to draw at
		* @param angle: the angle to draw the sprite at
		*/
		void draw(double newx, double newy, double angle);

		/** Get path to the sprite */
		const char* getPath();

		/**
		* Change angle of sprite object
		*
		* @param angle: the angle to draw the sprite at
		*/
		void setAngle(double newangle);

		/** Get the angle of the sprite object */
		double getAngle();

		/** Get a pointer to the details of the sprite in a Document object */
		rapidjson::Document* getSpriteDetails();

		/** Get width of sprite */
		int getWidth();

		/** Get height of sprite */
		int getHeight();

		/** Get name of sprite */
		const char* getName();
	private:
		SDL_Texture* texture;
		SDL_Surface* temp;
		SDL_Renderer* renderer;
		SDL_Rect rect;
		double angle;
		const char* name;
		const char* path;
		const char* detailspath;
		rapidjson::Document* sprite_details;
	};

	/** Confirm that details are in correct format and exist
	* @param details: the details Document object to look at
	*/
	bool validateDetails(rapidjson::Document* details);

	/** Check if two rectangles intersect - for collisions
	* @param a: the first rectangle
	* @param b: the second rectangle
	*/
	bool rectIntersect(SDL_Rect* a, SDL_Rect* b);
}