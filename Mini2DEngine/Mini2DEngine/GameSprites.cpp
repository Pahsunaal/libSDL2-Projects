#include "GameSprites.h"
#include <stdexcept>
#include <SDL_image.h>

using namespace GameSpr;

Sprite::Sprite(const char* path, SDL_Renderer* renderer) : path{ path }, renderer{ renderer }, angle{}, texture{}, rect{}, temp{ IMG_Load(path) } {
	if (!temp) throw std::runtime_error(IMG_GetError());
	texture = SDL_CreateTextureFromSurface(renderer, temp);
	rect.w = temp->w;
	rect.h = temp->h;
	SDL_FreeSurface(temp);
	printf("Sprite Created!\n");
}

Sprite::~Sprite() {
	if(texture) SDL_DestroyTexture(texture);
	printf("Sprite Destroyed!\n");
}

void Sprite::draw(double newx, double newy) {
	rect.x = (int)newx;
	rect.y = (int)newy;
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}

const char* Sprite::getPath() {
	return path;
}

void Sprite::setAngle(double newangle) {
	angle = newangle;
}

double Sprite::getAngle() {
	return angle;
}

