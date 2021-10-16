#pragma once
#include <SDL.h>

namespace GameSpr {
	struct Sprite {
		Sprite(const char* path, SDL_Renderer* renderer);
		~Sprite();
		void draw(double newx, double newy);
		void draw(double newx, double newy, double angle);
		const char* getPath();
		void setAngle(double newangle);
		double getAngle();
	private:
		SDL_Texture* texture;
		SDL_Surface* temp;
		SDL_Renderer* renderer;
		SDL_Rect rect;
		double angle;
		const char* path;
	};
}