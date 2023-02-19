//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DTextImp.h"
#include <stdexcept>

//--------------------------------------------------
//  Types
//--------------------------------------------------

using namespace Text;





//--------------------------------------------------
//  TextImp::TextImp() : .
//--------------------------------------------------
TextImp::TextImp(const char* fontpath,
				 int size,
				 const char* message,
				 SDL_Color color,
				 SDL_Renderer* renderer,
				 int width,
				 int height,
				 size_t index)
				 :
				 index{},
				 temp {},
				 texture{},
				 font{},
				 rect{},
				 renderer{ renderer },
				 message{ message },
				 size{ size },
				 color{ color },
				 width{ width },
				 height{ height },
				 angle{}
{
	font = TTF_OpenFont(fontpath, size); // Open the font file
	if (!font) throw std::runtime_error(TTF_GetError()); // Check for font load errors
	temp = TTF_RenderText_Solid(font, this->message.c_str(), color); // Create surface containing the text to dispplay
	texture = SDL_CreateTextureFromSurface(renderer, temp); // Create texture from surface
	SDL_FreeSurface(temp);
	
	// Get dimensions of texture to draw to render target
	rect.w = width;
	rect.h = height;
}





//--------------------------------------------------
//  TextImp::TextImp() : .
//--------------------------------------------------
TextImp::TextImp(const char* fontpath,
				 int size,
				 const char* message,
				 SDL_Color color,
				 SDL_Renderer* renderer,
				 size_t index)
				 :
				 index{},
				 temp {},
				 texture{},
				 font{},
				 rect{},
				 renderer{ renderer },
				 message{ message },
				 size{ size },
				 color{ color },
				 width{},
				 height{},
				 angle{}
{
	font = TTF_OpenFont(fontpath, size);
	if (!font) throw std::runtime_error(TTF_GetError());
	temp = TTF_RenderText_Solid(font, this->message.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, temp);
	width = temp->w;
	height = temp->h;
	rect.w = width;
	rect.h = height;
	SDL_FreeSurface(temp);
}





//--------------------------------------------------
//  TextImp::TextImp() : .
//--------------------------------------------------
TextImp::~TextImp()
{
	SDL_DestroyTexture(texture);
}





//--------------------------------------------------
//  TextImp::Draw() : .
//--------------------------------------------------
void TextImp::Draw(double newx, double newy)
{
	rect.x = (int)newx;
	rect.y = (int)newy;
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE); // Draws to render target
}





//--------------------------------------------------
//  TextImp::Draw() : .
//--------------------------------------------------
void TextImp::Draw(double newx, double newy, double angle)
{
	rect.x = (int)newx;
	rect.y = (int)newy;
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}





//--------------------------------------------------
//  TextImp::ChangeMessage() : .
//--------------------------------------------------
void TextImp::ChangeMessage(const char* newmessage, bool autoSize)
{
	message = newmessage;
	temp = TTF_RenderText_Solid(font, this->message.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, temp);

	// Get dimensions of texture to draw to render target
	if (autoSize) {
		width = temp->w;
		height = temp->h;
		rect.w = width;
		rect.h = height;
	}
	SDL_FreeSurface(temp);
}





//--------------------------------------------------
//  TextImp::DrawExt() : .
//--------------------------------------------------
void TextImp::DrawExt(double newx, double newy, double angle, const char* newmessage, bool autoSize)
{
	ChangeMessage(newmessage,autoSize);
	Draw(newx, newy, angle);
}





//--------------------------------------------------
//  TextImp::SetAngle() : .
//--------------------------------------------------
void TextImp::SetAngle(double newangle)
{
	angle = newangle;
}





//--------------------------------------------------
//  TextImp::GetAngle() : .
//--------------------------------------------------
double TextImp::GetAngle()
{
	return angle;
}





//--------------------------------------------------
//  TextImp::GetIndex() : .
//--------------------------------------------------
size_t TextImp::GetIndex()
{
	return index;
}





//--------------------------------------------------
//  TextImp::SetIndex() : .
//--------------------------------------------------
void TextImp::SetIndex(size_t newindex)
{
	index = newindex;
}
