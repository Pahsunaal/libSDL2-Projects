#ifndef M2D_TEXT_IH
#define M2D_TEXT_IH

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DText.h"

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace Text
{

class TextImp : public Text
{
public:
	TextImp(const char* fontpath, int size, const char* message, SDL_Color color, SDL_Renderer* renderer, int width, int height, size_t index);
	TextImp(const char* fontpath, int size, const char* message, SDL_Color color, SDL_Renderer* renderer, size_t index);
	~TextImp();

	// Interface

	void Draw(double newx, double newy);
	void Draw(double newx, double newy, double angle);
	void DrawExt(double newx, double newy, double angle, const char* newmessage, bool autoSize);
	void ChangeMessage(const char* newmessage, bool autoSize);
	void SetAngle(double newangle);
	double GetAngle();
	size_t GetIndex();

	// Engine

	void SetIndex(size_t index);
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
	size_t index;
};

}

#endif // M2D_TEXT_IH