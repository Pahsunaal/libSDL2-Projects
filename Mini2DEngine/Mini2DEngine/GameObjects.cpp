#include "GameObjects.h"
#include "Utilities.h"
#include <stdexcept>

#define KEYBOARD objMan->keyboard
#define MOUSE objMan->mouse
#define TEXT objMan->textMan

using namespace GameObj;
using namespace GameSpr;
using namespace GameRoom;
using namespace GameText;
using namespace IO;

#pragma region ObjectManager

ObjectManager::ObjectManager(SDL_Renderer* renderer, MouseInput* mouse, KeyboardInput* keyboard) : mouse{ mouse }, keyboard{ keyboard }, renderer{ renderer }, obj_array{}, num_obj{}, game_end{} {
	textMan = new TextManager{ renderer };
	roomMan = new RoomManager{};
	gameMan = new GameManager{ this };
}

ObjectManager::~ObjectManager() {
	delete gameMan;
	
	for (size_t i{}; i < num_obj; i++) {
		if(obj_array[i] != nullptr) delete obj_array[i];
		obj_array[i] = nullptr;
	}

	delete roomMan;
	delete textMan;
}

bool ObjectManager::update() {
	if (game_end) return false;
	for (size_t i{}; i < num_obj; i++) {
		auto obj = obj_array[i];
		if (obj) obj->update();
	}
	return true;
}

void ObjectManager::draw() {
	for (size_t i{}; i < num_obj; i++) {
		auto* obj = obj_array[i];
		if (obj) {
			obj->draw();
		}
	}
}

size_t ObjectManager::createObject(Object* obj) {
	try {
		obj_array[num_obj] = obj;
		num_obj++;

		if (obj->getToDestruct()) {
			destroyObject(num_obj);
			return -1;
		}

		return num_obj - 1;
	}
	catch (std::runtime_error e) {
		printf("Error loading object: %s", e.what());
		return -1;
	}
	catch (std::exception e) {
		printf("unknown exception: %s", e.what());
		return -1;
	}
}

void ObjectManager::destroyObject(size_t index) {
	if (obj_array[index] != nullptr) delete obj_array[index];
	
	obj_array[index] = nullptr;

	for (size_t i{ index }; i < max_obj - 1 && i < num_obj-1; i++) {
		obj_array[i] = obj_array[i + 1];
		obj_array[i]->index--;
	}
	//obj_array[index] = nullptr;
	obj_array[max_obj-1] = nullptr;
	num_obj--;
}

void ObjectManager::nextRoom() {
	if (roomMan->getCurrentRoom() < roomMan->getNumRooms()-1) {
		Room* room = roomMan->getRoomPointer(roomMan->getCurrentRoom());
		for (size_t i{}; i < room->getNumObjs(); i++) {
			destroyObject(*room->getObjectIndexFromArray(0));
		}
		//roomMan->destroyRoom();
	}
	else game_end = true;
}

void ObjectManager::gotoRoom(const char* name) {
	Room* room = roomMan->getRoomPointer(roomMan->getCurrentRoom());
	size_t num_objs_at_goto = room->getNumObjs();
	for (size_t i{}; i < num_objs_at_goto; i++) {

		size_t* world_obj_index = room->getObjectIndexFromArray(0);

		if (!obj_array[*world_obj_index]->getPersistent()) {
			room->removeObject(world_obj_index);
			destroyObject(*world_obj_index);
		}
		else {
			room->removeObject(world_obj_index);
			obj_array[*world_obj_index]->setRoom(nullptr);
		}
	}
	roomMan->selectRoom(name);
}

SDL_Renderer* ObjectManager::getRenderer() {
	return renderer;
}

size_t ObjectManager::getNumObj() {
	return num_obj;
}

#pragma endregion

#pragma region Object

Object::Object(ObjectManager* objMan, Room* room) : spr{}, hasSpr{}, x{}, y{}, objMan{ objMan }, persistent{}, room{ room }, toDestruct{}, direction{} {
	index = objMan->getNumObj();
	toDestruct = room->addObject(&index);
	//printf("Object created\n");
}

Object::~Object() {
	destroy();
	if(room) room->removeObject(&index);
	if(spr) delete spr;
	printf("Destroyed an object\n");
}

void Object::draw() {
	if(hasSpr) spr->draw(x,y,direction);
}

void Object::update() {

}

void Object::endUpdate() {

}

void Object::destroy() {

}

double Object::getX() {
	return x;
}

void Object::setX(double newx) {
	x = newx;
}

double Object::getY() {
	return y;
}

void Object::setY(double newy) {
	y = newy;
}

void Object::setXY(double newx, double newy) {
	x = newx;
	y = newy;
}

void Object::addX(double add) {
	x += add;
}

void Object::addY(double add) {
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

double Object::getDirection() {
	return direction;
}

void Object::setDirection(double newdirection) {
	direction = newdirection;
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

void Object::setRoom(Room* newroom) {
	room = newroom;
}

bool Object::getToDestruct() {
	return toDestruct;
}

bool Object::getPersistent() {
	return persistent;
}
#pragma endregion

#pragma region User Defined Objects

// Forward-Declare objects here
struct Template;
struct Test;
struct Game;
struct Ship;

struct Template : Object {
	Template(ObjectManager* objMan, Room* room) : Object{ objMan, room } {

	}
};

struct Test : Object {
	Test(ObjectManager* objMan, Room* room) : Object{ objMan, room } {
		setSprite("sprites\\Desert Tiles.png");
	}

	void update() override {
		if (MOUSE->getLeftButtonDown() || KEYBOARD->getKeyDown(SDL_SCANCODE_D)) {
			printf("Spr x: %d\n", getX());
			setXY(getX() + 5, getY() + 5);
		}
		else if (MOUSE->getRightButtonDown() || KEYBOARD->getKeyDown(SDL_SCANCODE_A)) {
			printf("Spr x: %d\n", getX());
			setXY(getX() - 5, getY() - 5);
		}
	}
};

struct Ship : Object {
	Ship(ObjectManager* objMan, Room* room) : Object{ objMan, room } {
		printf("Created the ship\n");
		setSprite("sprites\\ship.png");
		setXY(400, 400);

		speed = 0;
		decel = 0.9;
	}

	void update() override {
		speed *= 0.9;

		if (KEYBOARD->getKey(SDL_SCANCODE_RIGHT)) {
			setDirection(getDirection() + 5);
		}

		if (KEYBOARD->getKey(SDL_SCANCODE_LEFT)) {
			setDirection(getDirection() - 5);
		}

		if (KEYBOARD->getKey(SDL_SCANCODE_UP)) {
			if(speed < 12) speed += 0.5;
		}

		std::pair<double, double> vector = Utils::dirLenToVector(getDirection(), speed);
		//printf("%f, %f\n", vector.first,vector.second);
		addX(vector.first);
		addY(vector.second);
	}

	double speed;
	double decel;
};

struct Game : Object {
	Game(ObjectManager* objMan, Room* room) : Object{ objMan, room } {
		persistent = true;
		score = 0;
		lives = 3;
		SDL_Color white{ 255,255,255 };
		textTitle = TEXT->createText("fonts\\Hasklig-Medium.ttf", 24, "Space Rocks", white);
	}

	void update() override {
		if (KEYBOARD->getKeyDown(SDL_SCANCODE_RIGHT)) {
			auto room = objMan->roomMan->getRoomName(objMan->roomMan->getCurrentRoom());

			if (strcmp(room->c_str(),"start") == 0) {
				objMan->gotoRoom("game");
			}
		}
		if (score >= 1000) printf("Win!");
	}

	void draw() override {
		auto room = objMan->roomMan->getRoomName(objMan->roomMan->getCurrentRoom());

		if (strcmp(room->c_str(), "start") == 0) {
			textTitle->draw(400, 400);
		}
	}

	int score;
	int lives;
	Text* textTitle;
};



#pragma endregion

//Use GameManager as the starting point for all non-engine code - it creates all objects, and has it's own events system. It has no sprite.
#pragma region GameManager

GameManager::GameManager(ObjectManager* objMan) {
	printf("Created the gamemanager\n");

	objMan->roomMan->addRoom(Utils::getStringFromFile("rooms/start.txt"), 
		[objMan](Room* room) {
			objMan->createObject(new Game(objMan, room));
		}
	);
	objMan->roomMan->addRoom(Utils::getStringFromFile("rooms/game.txt"),
		[objMan](Room* room) {
			objMan->createObject(new Ship(objMan, room));
		}
	);
	

	objMan->roomMan->getRoomPointer(0)->roomStart();
}

GameManager::~GameManager() {
	printf("Destroyed the gamemanager\n");
}

#pragma endregion