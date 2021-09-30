#pragma once
#include "GameSprites.h"
#include "IOHandlers.h"

namespace GameObj {
	const size_t max_obj{ 100 };

	struct Object;

	struct ObjectManager {
		ObjectManager(SDL_Renderer* renderer, IO::MouseInput* mouse, IO::KeyboardInput* keyboard);
		~ObjectManager();
		void update();
		void draw();
		SDL_Renderer* getRenderer();
		size_t createObject(Object* obj);

		IO::MouseInput* mouse;
		IO::KeyboardInput* keyboard;
	private:
		Object* obj_array[max_obj];
		size_t num_obj;
		SDL_Renderer* renderer;
	};

	struct Object {
		Object(ObjectManager* objMan);
		~Object();
		virtual void update();
		virtual void endUpdate();
		virtual void draw();

		double get_x();
		void set_x(double newx);
		double get_y();
		void set_y(double newy);
		void set_xy(double newx, double newy);
		void add_x(double add);
		void add_y(double add);


		bool setSprite(const char* path);
		bool getHasSpr();
		const char* getSpritePath();
		GameSpr::Sprite* getSprite();
	protected:
		ObjectManager* objMan;
	private:
		bool hasSpr;
		GameSpr::Sprite* spr;
		double x;
		double y;
	};

	struct GameManager : Object {
		GameManager(ObjectManager* objMan);

		~GameManager();

		void update() override;

		void endUpdate() override;

		void draw() override;
	};
}

