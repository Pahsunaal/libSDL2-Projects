#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace GameText {
	const size_t max_texts{ 100 };

	struct Text {
		Text(const char* fontpath, int size, const char* message, SDL_Color color, SDL_Renderer* renderer, size_t index);
		Text(const char* fontpath, int size, const char* message, SDL_Color color, SDL_Renderer* renderer, int width, int height, size_t index);
		~Text();
		void draw(double newx, double newy);
		void draw(double newx, double newy, double angle);
		void drawExt(double newx, double newy, double angle, const char* newmessage, bool autoSize);
		void changeMessage(const char* newmessage, bool autoSize);
		void setAngle(double newangle);
		double getAngle();

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

	struct TextManager {
		TextManager(SDL_Renderer* renderer);
		~TextManager();
		Text* createText(const char* fontpath, int size, const char* message, SDL_Color color);
		Text* createText(const char* fontpath, int size, const char* message, SDL_Color color, int width, int height);
		void destroyText(Text* text);

	private:
		Text* text_array[max_texts];
		size_t num_texts;
		SDL_Renderer* renderer;
	};
}