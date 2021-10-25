#pragma once
#include "GameSprites.h"
#include "IOHandlers.h"
#include "GameRooms.h"
#include "GameText.h"
#include <map>

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
		void destroyObject(size_t index, bool room_end);
		void nextRoom();
		void gotoRoom(const char* name);
		void restartRoom();
		size_t getNumObj();

		template<typename T>
		T* getObject(size_t index);

		template<typename T>
		T* instance_find(size_t num);

		template<typename T>
		size_t instance_list(size_t* arraytofill);

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
		Object(ObjectManager* objMan, GameRoom::Room* room, double X, double Y);
		virtual ~Object();
		virtual void create();
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
		SDL_Rect* getColMask();


		bool setSprite(std::string* path);
		bool getHasSpr();
		const char* getSpritePath();
		GameSpr::Sprite* getSprite();

		void setRoom(GameRoom::Room* newroom);
		void setRoomEnd();
		GameRoom::Room* getRoom();
		void selfDestruct();
		bool getPersistent();
		bool getToDestruct();

		template<typename T>
		T* check_collision();

		size_t index;
	protected:
		ObjectManager* objMan;
		GameRoom::Room* room;
		bool persistent;
		bool room_end;
	private:
		bool toDestruct;
		bool hasSpr;
		GameSpr::Sprite* spr;
		SDL_Rect col_mask;
		double x;
		double y;
		double direction;
		
	};

	struct GameManager {
		GameManager(ObjectManager* objMan);

		~GameManager();
	};
}