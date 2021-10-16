#pragma once
#include "GameSprites.h"
#include "IOHandlers.h"
#include "GameRooms.h"
#include "GameText.h"

namespace GameObj {
	const size_t max_obj{ 100 };

	struct Object;
	
	struct GameManager;

	struct ObjectManager {
		ObjectManager(SDL_Renderer* renderer, IO::MouseInput* mouse, IO::KeyboardInput* keyboard);
		~ObjectManager();
		bool update();
		void draw();
		SDL_Renderer* getRenderer();
		size_t createObject(Object* obj);
		void destroyObject(size_t index);
		void nextRoom();
		void gotoRoom(const char* name);
		size_t getNumObj();

		IO::MouseInput* mouse;
		IO::KeyboardInput* keyboard;
		GameRoom::RoomManager* roomMan;
		GameText::TextManager* textMan;
	private:
		Object* obj_array[max_obj];
		size_t num_obj;
		bool game_end;
		SDL_Renderer* renderer;
		GameManager* gameMan;
		
	};

	struct Object {
		Object(ObjectManager* objMan, GameRoom::Room* room);
		~Object();
		virtual void update();
		virtual void endUpdate();
		virtual void draw();
		virtual void destroy();

		double getX();
		void setX(double newx);
		double getY();
		void setY(double newy);
		void setXY(double newx, double newy);
		void addX(double add);
		void addY(double add);
		double getDirection();
		void setDirection(double newdirection);


		bool setSprite(const char* path);
		bool getHasSpr();
		const char* getSpritePath();
		GameSpr::Sprite* getSprite();

		void setRoom(GameRoom::Room* newroom);
		bool getPersistent();
		bool getToDestruct();

		size_t index;
	protected:
		ObjectManager* objMan;
		GameRoom::Room* room;
		bool persistent;
	private:
		bool toDestruct;
		bool hasSpr;
		GameSpr::Sprite* spr;
		double x;
		double y;
		double direction;
		
	};

	struct GameManager {
		GameManager(ObjectManager* objMan);

		~GameManager();
	};
}