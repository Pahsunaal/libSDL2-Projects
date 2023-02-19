#ifndef M2D_SPRITE_IH
#define M2D_SPRITE_IH

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DSprite.h"

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace Spr
{

class SpriteImp : public Sprite
{
public:
	SpriteImp(const char* name, const char* path, const char* detailspath, SDL_Renderer* renderer);
	~SpriteImp();

	// Interface

	void Draw(double newx, double newy);
	void Draw(double newx, double newy, double angle);
	const char* GetPath();
	void SetAngle(double newangle);
	double GetAngle();
	rapidjson::Document* GetSpriteDetails();
	int GetWidth();
	int GetHeight();
	const char* GetName();
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

}

#endif // M2D_SPRITE_IH