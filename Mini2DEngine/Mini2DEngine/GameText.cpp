#include "GameText.h"
#include <stdexcept>

using namespace GameText;

#pragma region TextManager

TextManager::TextManager(SDL_Renderer* renderer) : text_array{}, num_texts{}, renderer{ renderer } {
	printf("Created the textmanager\n");
}

TextManager::~TextManager() {
	for (size_t i{}; i < num_texts; i++) {
		delete text_array[i];
		text_array[i] = nullptr;
	}
	printf("Destroyed the textmanager\n");
}

Text* TextManager::createText(const char* fontpath, int size, const char* message, SDL_Color color) {
	try {
		if (num_texts > max_texts) return NULL;
		Text* text = new Text{ fontpath,size,message,color,renderer,num_texts };
		text_array[num_texts] = text;
		num_texts++;
		return text;
	} catch (std::runtime_error e) {
		printf("Error loading object: %s", e.what());
		return NULL;
	}
}

Text* TextManager::createText(const char* fontpath, int size, const char* message, SDL_Color color, int width, int height) {
	try {
		if (num_texts > max_texts) return NULL;
		Text* text = new Text{ fontpath,size,message,color,renderer,width,height,num_texts };
		text_array[num_texts] = text;
		num_texts++;
		return text;
	} catch (std::runtime_error e) {
		printf("Error loading object: %s", e.what());
		return NULL;
	}
}

void TextManager::destroyText(Text* text) {
	size_t index = text->index;

	if (text_array[index] != nullptr) delete text_array[index];

	text_array[index] = nullptr;

	for (size_t i{ index }; i < max_texts - 1 && i < num_texts - 1; i++) {
		text_array[i] = text_array[i + 1];
		text_array[i]->index--;
	}
	//obj_array[index] = nullptr;
	text_array[max_texts - 1] = nullptr;
	num_texts--;
}

#pragma endregion

#pragma region Text

Text::Text(const char* fontpath, int size, const char* message, SDL_Color color, SDL_Renderer* renderer, int width, int height, size_t index) : index{}, temp {}, texture{}, font{}, rect{}, renderer{ renderer }, message{ message }, size{ size }, color{ color }, width{ width }, height{ height }, angle{} {
	font = TTF_OpenFont(fontpath, size);
	if (!font) throw std::runtime_error(TTF_GetError());
	temp = TTF_RenderText_Solid(font, this->message.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
	rect.w = width;
	rect.h = height;
}

Text::Text(const char* fontpath, int size, const char* message, SDL_Color color, SDL_Renderer* renderer, size_t index) : index{}, temp {}, texture{}, font{}, rect{}, renderer{ renderer }, message{ message }, size{ size }, color{ color }, width{}, height{}, angle{} {
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

Text::~Text() {
	SDL_DestroyTexture(texture);
}

void Text::draw(double newx, double newy) {
	rect.x = (int)newx;
	rect.y = (int)newy;
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}

void Text::draw(double newx, double newy, double angle) {
	rect.x = (int)newx;
	rect.y = (int)newy;
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}

void Text::changeMessage(const char* newmessage, bool autoSize) {
	message = newmessage;
	temp = TTF_RenderText_Solid(font, this->message.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, temp);
	if (autoSize) {
		width = temp->w;
		height = temp->h;
		rect.w = width;
		rect.h = height;
	}
	SDL_FreeSurface(temp);
}

void Text::drawExt(double newx, double newy, double angle, const char* newmessage, bool autoSize) {
	changeMessage(newmessage,autoSize);
	draw(newx, newy, angle);
}


void Text::setAngle(double newangle) {
	angle = newangle;
}

double Text::getAngle() {
	return angle;
}

#pragma endregion