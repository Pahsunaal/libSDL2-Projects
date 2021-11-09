/**
* @file Main.cpp
* @brief Handles core engine functions and main game loop. Remember to add libpng.dll, jpeg.dll etc to the builds because of nuget not working!
***************************************************/

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <stdexcept>
#include <climits>
#include <ctime>
#include "GameObjects.h"

using namespace IO;
using namespace GameSpr;
using namespace GameObj;

#pragma region Global Objects

SDL_Window* window{};
SDL_Renderer* renderer{};

#pragma endregion

/** Initialise game engine, including SDL, the window, and the renderer*/
bool init() {
	// Init SDL and check for failures - exit on fail
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Error in initialisation: %s", SDL_GetError());
		return false;
	}

	// Init SDL Image library and check for failures - exit on fail
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
		return false;
	}

	// Init SDL Text library and check for failures - exit on fail
	if (TTF_Init() < 0) {
		printf("TTF_Init: Failed to init required ttf support!\n");
		printf("TTF_Init: %s\n", TTF_GetError());
		return false;
	}

	// Create window and check for failures - exit on fail
	window = SDL_CreateWindow("Sprite Management", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
	if (!window) {
		printf("Error in window creation: %s", SDL_GetError());
		return false;
	}

	// Create renderer and check for failures - exit on fail
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer) {
		printf("Error in renderer creation: %s", SDL_GetError());
		return false;
	}

	// Ensure renderer target is cleared, and default draw color is white
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	return true;
}

/** Handle update (per-frame) of game logic. Includes event pipeline */
bool update(ObjectManager* obj_manager, MouseInput* mouse, KeyboardInput* keyboard) {
	SDL_Event e;
	srand((unsigned int)time(NULL)); // Ensures random numbers are random, uses sys time as seed

	// Reset render target - will likely be deprecated in the future for more precise control over graphics
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Main event control - polls all events
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
		case SDL_QUIT: // Exit game on process quit
			return false;
		case SDL_MOUSEBUTTONDOWN: // Set the mouse state when a mouse button is pressed
			mouse->setLeftButtonDown(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1));
			mouse->setRightButtonDown(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3));
			break;
		case SDL_MOUSEBUTTONUP:
			mouse->setLeftButtonUp(!(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1)) && mouse->getLeftButton());
			mouse->setRightButtonUp(!(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3)) && mouse->getRightButton());
			break;
		case SDL_KEYDOWN: // Set the keyboard state for the specific key pressed
			keyboard->setKeyDown(e.key.keysym.scancode, true);
			break;
		case SDL_KEYUP:
			keyboard->setKeyUp(e.key.keysym.scancode, true);
			break;
		}
	}

	// Updates GameObjects through obj_manager, and checks for exit calls
	if(!obj_manager->update()) return false;

	// Updates mouse and keyboard (for key pressed but not held events)
	mouse->endUpdate();
	keyboard->endUpdate();

	return true;
}

/** Call draw event of all objects through the object manager, and update screen with the render target */
bool draw(ObjectManager* obj_manager) {
	obj_manager->draw();
	SDL_RenderPresent(renderer);
	return true;
}

/** Safely exit the SDL environment and free resources from memory */
void kill(ObjectManager* obj_manager) {
	delete obj_manager;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

/** Main function - contains game loop */
int main(int argc, char** args) {
	const int MS_PER_FRAME = 16; // How long each frame is - 16ms is 60fps
	MouseInput mouse{};
	KeyboardInput keyboard{};

	// Ends process if init failed
	if (!init()) return 1;

	ObjectManager* obj_manager{ new ObjectManager{renderer,&mouse,&keyboard} };

	// Main game loop
	bool running{ true };
	while (running) {
		Uint32 startTicks = SDL_GetTicks();
		running = update(obj_manager,&mouse,&keyboard);
		draw(obj_manager);
		if(running) SDL_Delay(startTicks + MS_PER_FRAME - SDL_GetTicks()); // Ensures updates delayed to be at least 16ms apart
	}

	// When update() returns false, exit the game loop and kill the application
	kill(obj_manager);
	return 0;
}