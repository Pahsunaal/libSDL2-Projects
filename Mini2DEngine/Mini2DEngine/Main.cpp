#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <stdexcept>
#include <climits>
#include "GameObjects.h"

using namespace IO;
using namespace GameSpr;
using namespace GameObj;

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

//

// DYNAMIC GLOBAL OBJECTS:



//

bool init() {
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

	window = SDL_CreateWindow("Sprite Management", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
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

bool update(ObjectManager* obj_manager, MouseInput* mouse, KeyboardInput* keyboard) {
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

	obj_manager->update();

	mouse->endUpdate();
	keyboard->endUpdate();

	return true;
}

bool draw(ObjectManager* obj_manager) {
	obj_manager->draw();
	SDL_RenderPresent(renderer);
	return true;
}

void kill(ObjectManager* obj_manager) {
	delete obj_manager;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char** args) {
	const int MS_PER_FRAME = 16;
	MouseInput mouse{};
	KeyboardInput keyboard{};

	if (!init()) return 1;

	ObjectManager* obj_manager{ new ObjectManager{renderer,&mouse,&keyboard} };

	bool running{ true };
	while (running) {
		Uint32 startTicks = SDL_GetTicks();
		running = update(obj_manager,&mouse,&keyboard);
		draw(obj_manager);
		if(running) SDL_Delay(startTicks + MS_PER_FRAME - SDL_GetTicks());
	}

	kill(obj_manager);
	return 0;
}