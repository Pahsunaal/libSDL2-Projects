#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <stdexcept>
#include <climits>
#include "IOHandlers.h"

using namespace IO;

/*
*
*
* Remember to add libpng.dll,jpeg.dll etc to the builds because of nuget being weird!
*
*
*/

// GLOBAL OBJECTS:

SDL_Window* window{};
SDL_Renderer* renderer{};
const size_t max_spr{ 100 };

//

struct Sprite {
	Sprite(const char* path, int x, int y) : texture{}, temp{ IMG_Load(path) }, x{ x }, y{ y } {
		if (!temp) throw std::runtime_error(IMG_GetError());
		texture = SDL_CreateTextureFromSurface(renderer, temp);
		rect.x = x;
		rect.y = y;
		rect.w = temp->w;
		rect.h = temp->h;
		SDL_FreeSurface(temp);
		printf("Sprite Created!\n");
	}

	~Sprite() {
		SDL_DestroyTexture(texture);
		printf("Sprite Destroyed!\n");
	}

	void update() {
		rect.x = x;
		rect.y = y;
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	}

	// Unsafe, do not use unless through SpriteManager
	void set_xy(int newx, int newy) {
		x = newx;
		y = newy;
	}

	int get_x() {
		return x;
	}

	int get_y() {
		return y;
	}

private:
	SDL_Texture* texture;
	SDL_Surface* temp;
	SDL_Rect rect;
	int x;
	int y;
};

struct SpriteManager {
	SpriteManager() : spr_array{}, num_spr{} {
	}

	~SpriteManager() {
		for (size_t i{}; i < num_spr; i++) {
			delete spr_array[i];
			spr_array[i] = nullptr;
		}
	}

	void update() {
		for (size_t i{}; i < num_spr; i++) {
			auto spr = spr_array[i];
			if (spr) spr->update();
		}
	}

	bool set_spr_xy(size_t sprIndex, int x, int y) {
		if (sprIndex < 0 || sprIndex >= num_spr) return false;
		spr_array[sprIndex]->set_xy(x, y);
		return true;
	}

	int get_spr_x(size_t sprIndex) {
		return spr_array[sprIndex]->get_x();
	}

	int get_spr_y(size_t sprIndex) {
		if (sprIndex < 0 || sprIndex >= num_spr) return INT_MIN;
		return spr_array[sprIndex]->get_y();
	}

	size_t add_spr_from_path(const char* path, int x, int y) {
		try {
			spr_array[num_spr] = new Sprite{ path, x, y };
			num_spr++;
			return num_spr - 1;
		}
		catch (std::runtime_error e) {
			printf("Error loading sprite: %s", e.what());
			return -1;
		}
	}

private:
	Sprite* spr_array[max_spr];
	size_t num_spr;
};

// DYNAMIC GLOBAL OBJECTS:

SpriteManager* spr_manager{ new SpriteManager{} };

//

bool init(SpriteManager* spr_manager) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Error in initialisation: %s", SDL_GetError());
		return false;
	}

	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
		return false;
	}

	window = SDL_CreateWindow("Sprite Management", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	if (!window) {
		printf("Error in window creation: %s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("Error in renderer creation: %s", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	return true;
}

bool update(MouseInput* mouse, KeyboardInput* keyboard) {
	SDL_Event e;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
		case SDL_QUIT:
			return false;
		case SDL_MOUSEBUTTONDOWN:
			mouse->setLeftButtonDown(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1));
			mouse->setRightButtonDown(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3));
			break;
		case SDL_MOUSEBUTTONUP:
			mouse->setLeftButtonUp(!(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1)) && mouse->getLeftButton());
			mouse->setRightButtonUp(!(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3)) && mouse->getRightButton());
			break;
		case SDL_KEYDOWN:
			keyboard->setKeyDown(e.key.keysym.scancode,true);
			break;
		case SDL_KEYUP:
			keyboard->setKeyUp(e.key.keysym.scancode, true);
			break;
		}
	}

	if (mouse->getLeftButtonDown() || keyboard->getKeyDown(SDL_SCANCODE_D)) {
		printf("Spr x: %d\n", spr_manager->get_spr_x(0));
		spr_manager->set_spr_xy(0, spr_manager->get_spr_x(0) + 5, spr_manager->get_spr_y(0) + 5);
	}
	else if (mouse->getRightButtonDown() || keyboard->getKeyDown(SDL_SCANCODE_A)) {
		printf("Spr x: %d\n", spr_manager->get_spr_x(0));
		spr_manager->set_spr_xy(0, spr_manager->get_spr_x(0) - 5, spr_manager->get_spr_y(0) - 5);
	}

	spr_manager->update();

	mouse->endUpdate();
	keyboard->endUpdate();

	return true;
}

bool draw() {
	SDL_RenderPresent(renderer);
	
	return true;
}

void kill() {
	delete spr_manager;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char** args) {
	const int MS_PER_FRAME = 16;
	MouseInput mouse{};
	KeyboardInput keyboard{};

	if (!init(spr_manager)) return 1;

	size_t spr{ spr_manager->add_spr_from_path("sprites\\Desert Tiles.png",10,10) };
	if (spr < 0) return false;

	bool running{ true };
	while (running) {
		Uint32 startTicks = SDL_GetTicks();
		running = update(&mouse,&keyboard);
		draw();
		if(running) SDL_Delay(startTicks + MS_PER_FRAME - SDL_GetTicks());
	}

	kill();
	return 0;
}