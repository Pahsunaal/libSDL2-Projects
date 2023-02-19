#ifndef M2D_SPRITE_H
#define M2D_SPRITE_H

/**
* @file GameSprites.h
* @brief Handle sprites
***************************************************/

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include <SDL.h>
#include <rapidjson/document.h>

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace Spr {

/** Represents a texture to draw to the screen, storing important details about its position in-world */
class Sprite
{
public:
	/**
	* Construct new Sprite
	*
	* @param name: the name of the sprite
	* @param path: the path to the sprite's image file
	* @param path: the path to the sprite's properties file
	* @param renderer: the SDL_Renderer to use, as a pointer
	*/
	static Sprite* Create(const char* name, const char* path, const char* detailspath, SDL_Renderer* renderer);

	/** Destroys the sprite */
	virtual ~Sprite() = 0;

	/**
	* Draw the Sprite object at the given x and y
	*
	* @param newx: the x coordinate to draw at
	* @param newy: the y coordinate to draw at
	*/
	virtual void Draw(double newx, double newy) = 0;

	/**
	* Draw the sprite object at the given x and y, at an angle
	*
	* @param newx: the x coordinate to draw at
	* @param newy: the y coordinate to draw at
	* @param angle: the angle to draw the sprite at
	*/
	virtual void Draw(double newx, double newy, double angle) = 0;

	/** Get path to the sprite */
	virtual const char* GetPath() = 0;

	/**
	* Change angle of sprite object
	*
	* @param angle: the angle to draw the sprite at
	*/
	virtual void SetAngle(double newangle) = 0;

	/** Get the angle of the sprite object */
	virtual double GetAngle() = 0;

	/** Get a pointer to the details of the sprite in a Document object */
	virtual rapidjson::Document* GetSpriteDetails() = 0;

	/** Get width of sprite */
	virtual int GetWidth() = 0;

	/** Get height of sprite */
	virtual int GetHeight() = 0;

	/** Get name of sprite */
	virtual const char* GetName() = 0;
protected:
	Sprite(){};
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
bool ValidateDetails(rapidjson::Document* details);

/** Check if two rectangles intersect - for collisions
* @param a: the first rectangle
* @param b: the second rectangle
*/
bool RectIntersect(SDL_Rect* a, SDL_Rect* b);
}

#endif // M2D_SPRITE_H