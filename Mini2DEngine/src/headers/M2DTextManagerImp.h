#ifndef M2D_TEXT_MANAGER_IH
#define M2D_TEXT_MANAGER_IH

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DTextManager.h"

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace Txt
{

class Text;
class TextImp;

class TextManagerImp : public TextManager
{
public:
	TextManagerImp(SDL_Renderer* renderer);
	~TextManagerImp();

	Text* CreateText(const char* fontpath, int size, const char* message, SDL_Color color);
	Text* CreateText(const char* fontpath, int size, const char* message, SDL_Color color, int width, int height);
	void DestroyText(Text* text);
private:
	TextImp* text_array[max_texts];
	size_t num_texts;
	SDL_Renderer* renderer;
};

}

#endif // M2D_TEXT_MANAGER_IH