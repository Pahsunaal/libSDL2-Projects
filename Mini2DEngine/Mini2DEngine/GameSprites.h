#pragma once
#include <SDL.h>
#include <rapidjson/document.h>

namespace GameSpr {
	struct Sprite {
		Sprite(const char* name, const char* path, const char* detailspath, SDL_Renderer* renderer);
		~Sprite();
		void draw(double newx, double newy);
		void draw(double newx, double newy, double angle);
		const char* getPath();
		void setAngle(double newangle);
		double getAngle();
		rapidjson::Document* getSpriteDetails();
		int getWidth();
		int getHeight();
		const char* getName();
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

	bool validateDetails(rapidjson::Document* details);
	bool rectIntersect(SDL_Rect* a, SDL_Rect* b);
}