//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DSpriteImp.h"
#include <stdexcept>
#include <SDL_image.h>
#include "M2DUtilitiesImp.h"

//--------------------------------------------------
//  Types
//--------------------------------------------------

using namespace Spr;
using namespace rapidjson;
using namespace Utils;





//--------------------------------------------------
//  Sprite::Create() : .
//--------------------------------------------------
static Sprite* Create(const char* name, const char* path, const char* detailspath, SDL_Renderer* renderer)
{
	static SpriteImp sprite { name, path, detailspath, renderer };
	return &sprite;
}





//--------------------------------------------------
//  SpriteImp::SpriteImp() : .
//--------------------------------------------------
SpriteImp::SpriteImp(const char* name,
					 const char* path,
					 const char* detailspath,
					 SDL_Renderer* renderer)
					 :
					 name{ name },
					 path { path },
					 renderer{ renderer },
					 angle{},
					 texture{},
					 rect{},
					 temp{ IMG_Load(path) },
					 detailspath{ detailspath },
					 sprite_details{}
{
	if (!temp) throw std::runtime_error(IMG_GetError()); // Check image loaded successfully
	texture = SDL_CreateTextureFromSurface(renderer, temp);
	rect.w = temp->w;
	rect.h = temp->h;
	SDL_FreeSurface(temp);

	// Get the details from a file and parse them into a Document object
	std::string* doctext = Utils::getStringFromFile(detailspath);
	sprite_details = parseJSON((*doctext).c_str());
	delete doctext;

	// Validate the details and throw error if incorrect
	if (!ValidateDetails(sprite_details)) throw std::runtime_error("The sprite details do not contain required members!");
}





//--------------------------------------------------
//  SpriteImp::~SpriteImp() : .
//--------------------------------------------------
SpriteImp::~SpriteImp()
{
	if(texture) SDL_DestroyTexture(texture); // Check if the texture has been created first - it may not have been if an error occured
	delete sprite_details;
}





//--------------------------------------------------
//  SpriteImp::Draw() : .
//--------------------------------------------------
void SpriteImp::Draw(double newx, double newy)
{
	rect.x = (int)newx - (*sprite_details)["x_offset"].GetInt(); // Offset the x position of the sprite based on the offset (where the centre of the sprite is)
	rect.y = (int)newy - (*sprite_details)["y_offset"].GetInt();
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}





//--------------------------------------------------
//  SpriteImp::Draw() : .
//--------------------------------------------------
void SpriteImp::Draw(double newx, double newy, double angle)
{
	rect.x = (int)newx - (*sprite_details)["x_offset"].GetInt();
	rect.y = (int)newy - (*sprite_details)["y_offset"].GetInt();
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}





//--------------------------------------------------
//  SpriteImp::GetPath() : .
//--------------------------------------------------
const char* SpriteImp::GetPath()
{
	return path;
}





//--------------------------------------------------
//  SpriteImp::SetAngle() : .
//--------------------------------------------------
void SpriteImp::SetAngle(double newangle)
{
	angle = newangle;
}





//--------------------------------------------------
//  SpriteImp::GetAngle() : .
//--------------------------------------------------
double SpriteImp::GetAngle()
{
	return angle;
}





//--------------------------------------------------
//  SpriteImp::GetSpriteDetails() : .
//--------------------------------------------------
Document* SpriteImp::GetSpriteDetails()
{
	return sprite_details;
}





//--------------------------------------------------
//  SpriteImp::GetWidth() : .
//--------------------------------------------------
int SpriteImp::GetWidth()
{
	return rect.w;
}





//--------------------------------------------------
//  SpriteImp::GetHeight() : .
//--------------------------------------------------
int SpriteImp::GetHeight()
{
	return rect.h;
}





//--------------------------------------------------
//  SpriteImp::GetName() : .
//--------------------------------------------------
const char* SpriteImp::GetName()
{
	return name;
}





//--------------------------------------------------
//  Spr::ValidateDetails() : .
//--------------------------------------------------
bool Spr::ValidateDetails(rapidjson::Document* details)
{
	// Quick boolean check to see if the sprite has the required members
	bool result =
		details->HasMember("x_offset") &&
		details->HasMember("y_offset") &&
		details->HasMember("mask_left") &&
		details->HasMember("mask_right") &&
		details->HasMember("mask_top") &&
		details->HasMember("mask_bottom");
	return result;
}





//--------------------------------------------------
//  Spr::RectIntersect() : .
//--------------------------------------------------
bool Spr::RectIntersect(SDL_Rect* a, SDL_Rect* b)
{
	// Intersect code by Lazy Foo' Productions
	// https://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php

	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = (*a).x;
	rightA = (*a).x + (*a).w;
	topA = (*a).y;
	bottomA = (*a).y + (*a).h;

	//Calculate the sides of rect B
	leftB = (*b).x;
	rightB = (*b).x + (*b).w;
	topB = (*b).y;
	bottomB = (*b).y + (*b).h;
	

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
