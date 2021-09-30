#include "GameObjects.h"
#include <stdexcept>
#include "Utilities.h"
#define KEYBOARD objMan->keyboard
#define MOUSE objMan->mouse

using namespace GameObj;
using namespace GameSpr;
using namespace IO;

#pragma region ObjectManager

ObjectManager::ObjectManager(SDL_Renderer* renderer, MouseInput* mouse, KeyboardInput* keyboard) : mouse{ mouse }, keyboard{ keyboard }, renderer{ renderer }, obj_array{}, num_obj{} {
	createObject(new GameManager(this));
}

ObjectManager::~ObjectManager() {
	for (size_t i{}; i < num_obj; i++) {
		delete obj_array[i];
		obj_array[i] = nullptr;
	}
}

void ObjectManager::update() {
	for (size_t i{}; i < num_obj; i++) {
		auto obj = obj_array[i];
		if (obj) obj->update();
	}
}

void ObjectManager::draw() {
	for (size_t i{}; i < num_obj; i++) {
		auto* obj = obj_array[i];
		//
		if (obj) {
			//printf("%d", num_obj);
			//printf("%d\n", obj->getHasSpr());
			//if(obj->getHasSpr()) printf("%s",obj->getSpritePath());
			obj->draw();
		}
	}
}

size_t ObjectManager::createObject(Object* obj) {
	try {
		//printf("%p", obj);
		obj_array[num_obj] = obj;
		num_obj++;
		return num_obj - 1;
	}
	catch (std::runtime_error e) {
		printf("Error loading object: %s", e.what());
		return -1;
	}
}

SDL_Renderer* ObjectManager::getRenderer() {
	return renderer;
}

#pragma endregion

#pragma region Object

Object::Object(ObjectManager* objMan) : spr{}, hasSpr {}, x{}, y{}, objMan{ objMan } {
}

Object::~Object() {
	if(spr) delete spr;
}

void Object::draw() {
	if(hasSpr) spr->draw(x,y);
}

void Object::update() {

}

void Object::endUpdate() {

}

double Object::get_x() {
	return x;
}

void Object::set_x(double newx) {
	x = newx;
}

double Object::get_y() {
	return y;
}

void Object::set_y(double newy) {
	y = newy;
}

void Object::set_xy(double newx, double newy) {
	x = newx;
	y = newy;
}

void Object::add_x(double add) {
	x += add;
}

void Object::add_y(double add) {
	y += add;
}

bool Object::setSprite(const char* path) {
	Sprite* tmp = spr;
	
	try {
		spr = new Sprite{ path, objMan->getRenderer() };
		if (tmp) delete tmp;
		hasSpr = true;
		return true;
	}
	catch (std::runtime_error e) {
		printf("Error loading sprite: %s", e.what());
		return false;
	}
}

Sprite* Object::getSprite() {
	return spr;
}

bool Object::getHasSpr() {
	return hasSpr;
}

const char* Object::getSpritePath() {
	return spr->getPath();
}

#pragma endregion

#pragma region User Defined Objects

// Forward-Declare objects here
struct Template;
struct Test;
struct Game;
struct Ship;

struct Template : Object {
	Template(ObjectManager* objMan) : Object{ objMan } {

	}
};

struct Test : Object {
	Test(ObjectManager* objMan) : Object{ objMan } {
		setSprite("sprites\\Desert Tiles.png");
	}

	void update() override {
		if (MOUSE->getLeftButtonDown() || KEYBOARD->getKeyDown(SDL_SCANCODE_D)) {
			printf("Spr x: %d\n", get_x());
			set_xy(get_x() + 5, get_y() + 5);
		}
		else if (MOUSE->getRightButtonDown() || KEYBOARD->getKeyDown(SDL_SCANCODE_A)) {
			printf("Spr x: %d\n", get_x());
			set_xy(get_x() - 5, get_y() - 5);
		}
	}
};

struct Ship : Object {
	Ship(ObjectManager* objMan) : Object{ objMan } {
		setSprite("sprites\\ship.png");
		set_xy(400, 400);

		speed = 0;
		decel = 0.9;
	}

	void update() override {
		speed *= 0.9;

		if (KEYBOARD->getKey(SDL_SCANCODE_RIGHT)) {
			getSprite()->setAngle(getSprite()->getAngle() + 5);
		}

		if (KEYBOARD->getKey(SDL_SCANCODE_LEFT)) {
			getSprite()->setAngle(getSprite()->getAngle() - 5);
		}

		if (KEYBOARD->getKey(SDL_SCANCODE_UP)) {
			if(speed < 12) speed += 0.05;
		}

		std::pair<double, double> vector = Utils::dirLenToVector(getSprite()->getAngle(), speed);
		printf("%f, %f\n", vector.first,vector.second);
		add_x(vector.first);
		add_y(vector.second);
	}

	double speed;
	double decel;
};

struct Game : Object {
	Game(ObjectManager* objMan) : Object{ objMan } {
		score = 0;
		lives = 3;

		objMan->createObject(new Ship(objMan));
	}

	void update() override {
		if (score >= 1000) printf("Win!");
	}

	int score;
	int lives;
};



#pragma endregion

//Use GameManager as the starting point for all non-engine code - it creates all objects, and has it's own events system. It has no sprite.
#pragma region GameManager

GameManager::GameManager(ObjectManager* objMan) : Object{ objMan } {
	printf("Created the gamemanager\n");

	//objMan->createObject(new Test(objMan));
	objMan->createObject(new Game(objMan));
}

GameManager::~GameManager() {

}

void GameManager::update() {

}

void GameManager::endUpdate() {

}

void GameManager::draw() {

}

#pragma endregion