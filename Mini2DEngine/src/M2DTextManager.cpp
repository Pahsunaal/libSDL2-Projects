//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DTextManagerImp.h"
#include "M2DTextImp.h"
#include <stdexcept>

//--------------------------------------------------
//  Types
//--------------------------------------------------

using namespace Txt;





//--------------------------------------------------
//  TextManagerImp::TextManagerImp() : .
//--------------------------------------------------
TextManagerImp::TextManagerImp(SDL_Renderer* renderer) : text_array{}, num_texts{}, renderer{ renderer } {
	printf("Created the textmanager\n");
}





//--------------------------------------------------
//  TextManagerImp::~TextManagerImp() : .
//--------------------------------------------------
TextManagerImp::~TextManagerImp() {
	for (size_t i{}; i < num_texts; i++) {
		delete text_array[i];
		text_array[i] = nullptr;
	}
	printf("Destroyed the textmanager\n");
}





//--------------------------------------------------
//  TextManagerImp::CreateText() : .
//--------------------------------------------------
Text* TextManagerImp::CreateText(const char* fontpath, int size, const char* message, SDL_Color color) {
	// Catch errors on object creation
	try {
		if (num_texts > max_texts) return NULL; // Check if over max number of texts
		TextImp* text = new TextImp{ fontpath,size,message,color,renderer,num_texts };
		text_array[num_texts] = text; // Put the text in the text_array
		num_texts++;
		return text; // Return pointer to the created object
	} catch (std::runtime_error e) {
		printf("Error loading object: %s", e.what());
		return NULL;
	}
}





//--------------------------------------------------
//  TextManagerImp::CreateText() : .
//--------------------------------------------------
Text* TextManagerImp::CreateText(const char* fontpath, int size, const char* message, SDL_Color color, int width, int height) {
	try {
		if (num_texts > max_texts) return NULL;
		TextImp* text = new TextImp{ fontpath,size,message,color,renderer,width,height,num_texts };
		text_array[num_texts] = text;
		num_texts++;
		return text;
	} catch (std::runtime_error e) {
		printf("Error loading object: %s", e.what());
		return NULL;
	}
}





//--------------------------------------------------
//  TextManagerImp::DestroyText() : .
//--------------------------------------------------
void TextManagerImp::DestroyText(Text* text) {
	size_t index = text->GetIndex();

	if (text_array[index] != nullptr) delete text_array[index]; // Delete the Text object if it exists

	text_array[index] = nullptr; // Repoint the index to nullptr

	// Move adjacemt Text objects back one index
	for (size_t i{ index }; i < max_texts - 1 && i < num_texts - 1; i++) {
		text_array[i] = text_array[i + 1];
		text_array[i]->SetIndex(text->GetIndex()-1);
	}
	text_array[max_texts - 1] = nullptr;
	num_texts--;
}