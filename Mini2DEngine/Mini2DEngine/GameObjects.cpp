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

using namespace std::string_literals;

#pragma region ObjectManager

ObjectManager::ObjectManager(SDL_Renderer* renderer, MouseInput* mouse, KeyboardInput* keyboard) : mouse{ mouse }, keyboard{ keyboard }, renderer{ renderer }, obj_array{}, num_obj{}, game_end{} {
	// Init additional managers
	textMan = new TextManager{ renderer };
	roomMan = new RoomManager{};
	gameMan = new GameManager{ this };
}

ObjectManager::~ObjectManager() {
	delete gameMan;
	
	// Destroy each object in the game
	for (size_t i{}; i < num_obj; i++) {
		destroyObject(i, true);
	}

	// Free each manager
	delete roomMan;
	delete textMan;
}

bool ObjectManager::update() {
	if (game_end) return false; // Check if game has ended and pass back up to update() in Main.cpp
	for (size_t i{}; i < num_obj; i++) {
		auto obj = obj_array[i];
		if (obj) {
			obj->update();
			if (obj->getToDestruct()) destroyObject(obj->index,false); // Destroy objects flagged for destruction
		}
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

		if (obj->getToDestruct()) { // Checks if object creation was unsuccessful but didn't trigger exception, and destroys it
			destroyObject(num_obj,false);
			return -1;
		}

		obj->create();
		return num_obj - 1;
	}
	catch (std::runtime_error e) {
		printf("Error loading object: %s", e.what()); // May have problems with creating sprites etc
		return -1;
	}
	catch (std::exception e) {
		printf("unknown exception: %s", e.what());
		return -1;
	}
}

void ObjectManager::destroyObject(size_t index, bool room_end) {
	if (index >= num_obj || index >= max_obj) return; // Check bounds
	if (obj_array[index] != nullptr) {
		auto obj = obj_array[index];
		if(room_end) obj->setRoomEnd(); // Indicates to object whether the room will be ending

		// Untangles object from room
		Room* room = roomMan->getRoomPointer(roomMan->getCurrentRoom());
		if(obj->getRoom()) room->removeObject(&(obj->index));
		delete obj_array[index];
	}
	obj_array[index] = nullptr;
	
	// Shifts rest of array back one index
	for (size_t i{ index }; i < max_obj - 1 && i < num_obj-1; i++) {
		obj_array[i] = obj_array[i + 1];
		obj_array[i]->index--;
	}

	obj_array[max_obj-1] = nullptr;
	num_obj--;
}

void ObjectManager::nextRoom() {
	if (roomMan->getCurrentRoom() < roomMan->getNumRooms()-1) {
		Room* room = roomMan->getRoomPointer(roomMan->getCurrentRoom());

		// Destroy every object in the room
		for (size_t i{}; i < room->getNumObjs(); i++) {
			destroyObject(*room->getObjectIndexFromArray(0),true);
		}
	}
	else game_end = true; // Trying to go the next room when no more exists ends the game
}

void ObjectManager::gotoRoom(const char* name) {
	Room* room = roomMan->getRoomPointer(roomMan->getCurrentRoom());
	size_t num_objs_at_goto = room->getNumObjs();
	for (size_t i{}; i < num_objs_at_goto; i++) {

		size_t* world_obj_index = room->getObjectIndexFromArray(0);

		// Untangles persistent objects or destroys non-persistent objects
		if (!obj_array[*world_obj_index]->getPersistent()) {
			destroyObject(*world_obj_index,true);
		}
		else {
			room->removeObject(world_obj_index);
			obj_array[*world_obj_index]->setRoom(nullptr);
		}
	}
	roomMan->selectRoom(name);
}

void ObjectManager::restartRoom() {
	Room* room = roomMan->getRoomPointer(roomMan->getCurrentRoom());
	size_t num_objs_at_goto = room->getNumObjs();
	for (size_t i{}; i < num_objs_at_goto; i++) {

		size_t* world_obj_index = room->getObjectIndexFromArray(0);

		if (!obj_array[*world_obj_index]->getPersistent()) {
			destroyObject(*world_obj_index,true);
		}
		else {
			room->removeObject(world_obj_index);
			obj_array[*world_obj_index]->setRoom(nullptr);
		}
	}
	roomMan->restartRoom();
}

SDL_Renderer* ObjectManager::getRenderer() {
	return renderer;
}

size_t ObjectManager::getNumObj() {
	return num_obj;
}

template<typename T>
T* ObjectManager::getObject(size_t index) {
	if(index < num_obj) return dynamic_cast<T*>(obj_array[index]); // Type casts Object* to type of requested object. Can cause errors, watch out!
	return nullptr;
}

template<typename T>
T* ObjectManager::instance_find(size_t num) {
	size_t count{};
	for (size_t i{}; i < num_obj; i++) {
		T* ptr = dynamic_cast<T*>(obj_array[i]);
		if (ptr && typeid(*ptr) == typeid(T)) {
			count++;
		}
		if (ptr && count == num) {
			return ptr;
		}
	}
	return nullptr;
}

template<typename T>
size_t ObjectManager::instance_list(size_t* arraytofill) {
	size_t count{};
	for (size_t i{}; i < num_obj; i++) {
		T* ptr = dynamic_cast<T*>(obj_array[i]);
		if (ptr && typeid(*ptr) == typeid(T)) {
			arraytofill[count] = i;
			count++;
		}
	}
	return count;
}

#pragma endregion

#pragma region Object

Object::Object(ObjectManager* objMan, Room* room, double X, double Y) : spr{}, hasSpr{}, x{ X }, y{ Y }, objMan{ objMan }, persistent{}, room{ room }, toDestruct{}, direction{}, col_mask{}, room_end{} {
	index = objMan->getNumObj();
	toDestruct = room->addObject(&index);
	
}

Object::~Object() {
	if(spr) delete spr;
}

void Object::create() {

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

	// Update collision mask position if it exists
	if (hasSpr) {
		rapidjson::Document* details = spr->getSpriteDetails();

		col_mask.x = x - (*details)["x_offset"].GetInt() + (*details)["mask_left"].GetInt();
	}
}

double Object::getY() {
	return y;
}

void Object::setY(double newy) {
	y = newy;

	// Update collision mask position if it exists
	if (hasSpr) {
		rapidjson::Document* details = spr->getSpriteDetails();

		col_mask.y = y - (*details)["y_offset"].GetInt() + (*details)["mask_top"].GetInt();
	}
}

void Object::setXY(double newx, double newy) {
	x = newx;
	y = newy;

	// Update collision mask position if it exists
	if (hasSpr) {
		rapidjson::Document* details = spr->getSpriteDetails();

		col_mask.x = x - (*details)["x_offset"].GetInt() + (*details)["mask_left"].GetInt();
		col_mask.y = y - (*details)["y_offset"].GetInt() + (*details)["mask_top"].GetInt();
	}
}

void Object::addX(double add) {
	x += add;

	// Update collision mask position if it exists
	if (hasSpr) {
		rapidjson::Document* details = spr->getSpriteDetails();

		col_mask.x = x - (*details)["x_offset"].GetInt() + (*details)["mask_left"].GetInt();
	}
}

void Object::addY(double add) {
	y += add;

	// Update collision mask position if it exists
	if (hasSpr) {
		rapidjson::Document* details = spr->getSpriteDetails();

		col_mask.y = y - (*details)["y_offset"].GetInt() + (*details)["mask_top"].GetInt();
	}
}

bool Object::setSprite(std::string* name) {
	Sprite* tmp = spr;

	// Determine path of sprite based on name and rigid structure
	std::string imgpath = "sprites\\" + *name + "\\" + *name + ".png";
	std::string detailspath = "sprites\\" + *name + "\\" + *name + ".json";
	
	try {
		spr = new Sprite{ name->c_str(), imgpath.c_str(), detailspath.c_str(), objMan->getRenderer() };
		if (tmp) delete tmp; // Frees the old sprite if it existed
		hasSpr = true;

		rapidjson::Document* details = spr->getSpriteDetails();

		// Update collision mask position
		col_mask.x = x - (*details)["x_offset"].GetInt() + (*details)["mask_left"].GetInt();
		col_mask.w = (*details)["mask_right"].GetInt() - (*details)["mask_left"].GetInt();
		col_mask.y = y - (*details)["y_offset"].GetInt() + (*details)["mask_top"].GetInt();
		col_mask.h = (*details)["mask_bottom"].GetInt() - (*details)["mask_top"].GetInt();

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

void Object::setRoomEnd() {
	room_end = true;
}

GameRoom::Room* Object::getRoom() {
	return room;
}

bool Object::getToDestruct() {
	return toDestruct;
}

bool Object::getPersistent() {
	return persistent;
}

SDL_Rect* Object::getColMask() {
	return &col_mask;
}

void Object::selfDestruct() {
	toDestruct = true;
}

template<typename T>
T* Object::check_collision() {
	size_t arraytofill[max_obj]{};

	size_t num = objMan->instance_list<T>(arraytofill);

	// Checks for a rectangle intersection on the collision mask of the current object and each object of the requested type
	for (size_t i{}; i < num; i++) {
		T* obj = objMan->getObject<T>(arraytofill[i]);
		auto result = rectIntersect(&col_mask, obj->getColMask());
		if (result) {
			return obj;
		}
	}
	return nullptr;
}
#pragma endregion

#pragma region User Defined Objects

// Forward-Declare objects here

/** A basic example for how objects should be structured*/
struct Template : Object {
	Template(ObjectManager* objMan, Room* room, double X, double Y) : Object{ objMan, room, X, Y } {

	}
};

/// @private
struct Asteroid : Object {
	Asteroid(ObjectManager* objMan, Room* room, double X, double Y, const char* sprname);
	~Asteroid();
	void create() override;
	void destroy() override;
	void update() override;
	std::string sprname;

	double maxSpeed = 3;
	double speed = 0;
};

/// @private
struct Game : Object {
	Game(ObjectManager* objMan, Room* room, double X, double Y) : Object{ objMan, room, X, Y } {
	}

	void create() override {
		persistent = true;
		score = 0;
		lives = 3;
		SDL_Color white{ 255,255,255 };

		// Text objects
		textTitle = TEXT->createText("fonts\\Hasklig-Medium.ttf", 36, "Space Rocks", white);
		textScore = TEXT->createText("fonts\\Hasklig-Medium.ttf", 24, "Score: 0", white);
		textLives = TEXT->createText("fonts\\Hasklig-Medium.ttf", 24, "Lives: XXX", white);
		textGameover = TEXT->createText("fonts\\Hasklig-Medium.ttf", 28, "Game Over!", white);
		textWin = TEXT->createText("fonts\\Hasklig-Medium.ttf", 28, "You Won!", white);
		textPressPlay = TEXT->createText("fonts\\Hasklig-Medium.ttf", 24, "Press ENTER to play", white);

		alarm0 = 0;

		// Create asteroids in title room
		for (int i{}; i < 6; i++) {
			double xx = rand() % room->getWidth();
			double yy = rand() % room->getHeight();

			objMan->createObject(new Asteroid(objMan, room, xx, yy, asteroidTypes[rand() % 3]));
		}
	}

	void update() override {
		auto roomname = objMan->roomMan->getRoomName(objMan->roomMan->getCurrentRoom());
		Room* roomCur = objMan->roomMan->getRoomPointer(objMan->roomMan->getCurrentRoom());
		
		// If enter pressed
		if (KEYBOARD->getKeyDown(SDL_SCANCODE_RETURN)) {
			if (strcmp(roomname->c_str(), "start") == 0) {
				objMan->gotoRoom("game");
			} else if ((strcmp(roomname->c_str(), "gameover") == 0) || (strcmp(roomname->c_str(), "win") == 0)) {
				score = 0;
				lives = 3;
				objMan->gotoRoom("game");
			}
		}
		
		// Timer increments and creates asteroids every 4 seconds
		if (strcmp(roomname->c_str(), "game") == 0) {
			alarm0++;
			if (alarm0 > 60 * 4) {
				alarm0 = 0;
				double xx{};
				double yy{};
				if (Utils::choose(0, 1) == 0) {
					xx = Utils::choose(0, roomCur->getWidth());
					yy = rand() % roomCur->getHeight();
				}
				else {
					xx = rand() % roomCur->getWidth();
					yy = Utils::choose(0, roomCur->getHeight());
				}

				objMan->createObject(new Asteroid(objMan, roomCur, xx, yy, asteroidTypes[rand() % 3]));
			}

			if (lives <= 0) {
				objMan->gotoRoom("gameover");
			}

			if (score >= 1000) {
				objMan->gotoRoom("win");
			}
		}
	}

	void draw() override {
		auto roomname = objMan->roomMan->getRoomName(objMan->roomMan->getCurrentRoom());

		if (strcmp(roomname->c_str(), "start") == 0) {
			textTitle->draw(10, 10);
			textPressPlay->draw(20, 550);
		}
		else if (strcmp(roomname->c_str(), "game") == 0) {
			textScore->changeMessage(("Score: " + std::to_string(score)).c_str(), true);
			textScore->draw(10, 10);
			textLives->changeMessage(("Lives: " + std::to_string(lives)).c_str(), true);
			textLives->draw(10, 760);
		}
		else if (strcmp(roomname->c_str(), "gameover") == 0) {
			textGameover->draw(20, 200);
			textPressPlay->draw(20, 550);
			textScore->changeMessage(("Score: " + std::to_string(score)).c_str(), true);
			textScore->draw(40, 250);
		}
		else if (strcmp(roomname->c_str(), "win") == 0) {
			textWin->draw(20, 250);
			textPressPlay->draw(20, 550);
		}
	}

	int score;
	int lives;
	size_t alarm0;
	Text* textTitle;
	Text* textScore;
	Text* textLives;
	Text* textGameover;
	Text* textWin;
	Text* textPressPlay;
	const char* asteroidTypes[3]{ "largeAsteroid","medAsteroid","smallAsteroid" };
};

struct Ship;

/// @private
struct Bullet : Object {
	Bullet(ObjectManager* objMan, Room* room, double X, double Y);
	void create() override;
	void update() override;
	double speed = 6;
	std::string sprname = "bullet";
};

/// @private
struct Ship : Object {
	Ship(ObjectManager* objMan, Room* room, double X, double Y) : Object{ objMan, room, X, Y } {
	}

	void create() override {
		setSprite(&sprname);

		speed = 0;
		decel = 0.9;
	}

	void update() override {
		speed *= 0.9;

		if (KEYBOARD->getKey(SDL_SCANCODE_RIGHT)) {
			setDirection(getDirection() + 4);
		}

		if (KEYBOARD->getKey(SDL_SCANCODE_LEFT)) {
			setDirection(getDirection() - 4);
		}

		if (KEYBOARD->getKey(SDL_SCANCODE_UP)) {
			if (speed < 10) speed += 0.3;
		}

		if (KEYBOARD->getKeyDown(SDL_SCANCODE_SPACE)) {
			objMan->createObject(new Bullet(objMan, room, getX(), getY()));
		}

		// Figure out where ship should be based on speed and direction
		std::pair<double, double> vector = Utils::dirLenToVector(getDirection(), speed);
		addX(vector.first);
		addY(vector.second);

		// Handle loop around
		if (getX() > room->getWidth()) {
			setX(0);
		}
		else if (getX() < 0) {
			setX(room->getWidth());
		}

		if (getY() > room->getHeight()) {
			setY(0);
		}
		else if (getY() < 0) {
			setY(room->getHeight());
		}

		// Check for collisions and restart room with one less life if it occurs
		if (check_collision<Asteroid>()) {
			objMan->instance_find<Game>(1)->lives--;
			objMan->restartRoom();
		}

	}

	std::string sprname = "ship";
	double speed;
	double decel;
};

#pragma region Bullet

Bullet::Bullet(ObjectManager* objMan, Room* room, double X, double Y) : Object{ objMan, room, X, Y } {
}

void Bullet::create() {
	setSprite(&sprname);

	// Bullet set to same direction as ship
	setDirection(objMan->instance_find<Ship>(1)->getDirection());
}

void Bullet::update() {
	// Figure out where ship should be based on speed and direction
	std::pair<double, double> vector = Utils::dirLenToVector(getDirection(), speed);

	addX(vector.first);
	addY(vector.second);

	// Check for collision with asteroid and trigger relevant destruction and score increment
	auto col = check_collision<Asteroid>();
	if (col) {
		objMan->instance_find<Game>(1)->score+=10;
		col->selfDestruct();
		selfDestruct();
	}

	// Destroy object if it goes out of bounds
	if (getX() > room->getWidth() || getY() > room->getHeight() || getY() < 0 || getX() < 0) {
		selfDestruct();
	}
}

#pragma endregion

#pragma region Asteroid

Asteroid::Asteroid(ObjectManager* objMan, Room* room, double X, double Y, const char* sprname) : Object{ objMan, room, X, Y } {
	this->sprname = sprname;
}

Asteroid::~Asteroid() {
	if(!room_end) destroy(); // only perform breaking up of asteroid when the room isnt ending
}

void Asteroid::create() {
	setSprite(&(this->sprname));

	// Pick random speeds and directions
	setDirection(Utils::randDouble(360.0));
	speed = Utils::randDouble(maxSpeed) + 1;
}

void Asteroid::destroy() {
	// Create increasingly smaller asteroids when destroyed
	if (strcmp(getSprite()->getName(), "largeAsteroid") == 0) {
		for (int i{}; i < 2; i++) objMan->createObject(new Asteroid(objMan, room, getX(), getY(), "medAsteroid"));
	}
	if (strcmp(getSprite()->getName(), "medAsteroid") == 0) {
		for (int i{}; i < 2; i++)  objMan->createObject(new Asteroid(objMan, room, getX(), getY(), "smallAsteroid"));
	}
}

void Asteroid::update() {
	// Figure out where ship should be based on speed and direction
	std::pair<double, double> vector = Utils::dirLenToVector(getDirection(), speed);

	addX(vector.first);
	addY(vector.second);

	// Handle out of bounds looping
	if (getX() > room->getWidth()) {
		setX(0);
	}
	else if (getX() < 0) {
		setX(room->getWidth());
	}

	if (getY() > room->getHeight()) {
		setY(0);
	}
	else if (getY() < 0) {
		setY(room->getHeight());
	}
}

#pragma endregion

#pragma endregion

//Use GameManager as the starting point for all non-engine code - it creates all objects, and has it's own events system. It has no sprite.
#pragma region GameManager

GameManager::GameManager(ObjectManager* objMan) {
	printf("Created the gamemanager\n");

	// Add the start room
	objMan->roomMan->addRoom(Utils::getStringFromFile("rooms/start.txt"), 
		[objMan](Room* room) {
			objMan->createObject(new Game(objMan, room,0,0));
		}
	);

	// Add the game room
	objMan->roomMan->addRoom(Utils::getStringFromFile("rooms/game.txt"),
		[objMan](Room* room) {
			objMan->createObject(new Ship(objMan, room,400,400));
			const char* asteroidTypes[3]{ "largeAsteroid","medAsteroid","smallAsteroid" };
			for (int i{}; i < 6; i++) {
				double xx{};
				double yy{};
				if (Utils::choose(0, 1) == 0) {
					xx = Utils::choose(0, room->getWidth());
					yy = rand() % room->getHeight();
				}
				else {
					xx = rand() % room->getWidth();
					yy = Utils::choose(0, room->getHeight());
				}
				
				objMan->createObject(new Asteroid(objMan, room, xx, yy, asteroidTypes[rand() % 3]));
			}
		}
	);
	
	// Add the game over room
	objMan->roomMan->addRoom(Utils::getStringFromFile("rooms/gameover.txt"),
		[objMan](Room* room) {

		}
	);

	// Add the win room
	objMan->roomMan->addRoom(Utils::getStringFromFile("rooms/win.txt"),
		[objMan](Room* room) {

		}
	);

	// Start the first room
	objMan->roomMan->getRoomPointer(0)->roomStart();
}

GameManager::~GameManager() {

}

#pragma endregion