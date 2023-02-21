# mini2dengine

Currently on hiatus.

This is my work-in-progress implementation of a basic 2D game engine written in C++ using the SDL2 library.

Previously, this repo was called libSDL2-Projects and contained a small collection of other little programs, but these have been removed.

This project is a simple 2D game engine for SDL2 that I can use to create a variety of different games. I will be adding to it slowly as I learn more about engines and C++.

## Documentation

You can find the documentation for Mini2DEngine in the docs folder. It is available in HTML or LaTeX produced PDFs

## Basic Usage

All user code can be contained within the User Defined Objects pragma region within GameObjects.cpp. The aim of this is to reduce the necessity to interact with the engines inner workings and to prevent need for redundant header code in small projects.

Add rooms in the constructor of the GameManager. User objects should correctly inherit from Object. If overriding destroy(), you should also override the destructor so that the derived destroy() event is run instead.

## ASTEROIDS

Enough features have been added that I was able to create my first game using this engine! It acts as the demonstration game for the engine itself. Based on the arcade classic Asteroids, the aim is to get to 1000 points by breaking up asteroids whilst avoiding them.

Simply download the .ZIP file, extract it, and run the .exe.

### Controls

Left/Right - Turn

Up - Forward

Space - Shoot

Enter - Start/Restart the game
