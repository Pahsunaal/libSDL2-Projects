//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DObjectManagerImp.h"
#include "M2DGameManagerImp.h"
#include "M2DObjectImp.h"
#include "M2DUtilitiesImp.h"
#include "M2DKeyboardIO.h"
#include "M2DMouseIO.h"
#include "M2DText.h"
#include "M2DSprite.h"
#include <stdexcept>

//--------------------------------------------------
//  Defines
//--------------------------------------------------

#define KEYBOARD objMan->keyboard
#define MOUSE objMan->mouse
#define TEXT objMan->textMan

//--------------------------------------------------
//  Types
//--------------------------------------------------

using namespace Obj;
using namespace Spr;
using namespace Room;
using namespace Txt;
using namespace IO;
using namespace std::string_literals;





//--------------------------------------------------
//  ObjectManagerImp::ObjectManagerImp() : .
//--------------------------------------------------
ObjectManagerImp::ObjectManagerImp(SDL_Renderer* renderer,
								   MouseInput* mouse,
								   KeyboardInput* keyboard)
								   :
								   mouse{ mouse },
								   keyboard{ keyboard },
								   renderer{ renderer },
								   obj_array{},
								   num_obj{},
								   game_end{}
{
	// Init additional managers
	textMan = new TextManagerImp{ renderer };
	roomMan = new RoomManagerImp{};
	gameMan = new GameManagerImp{ this };
}





//--------------------------------------------------
//  ObjectManagerImp::ObjectManagerImp() : .
//--------------------------------------------------
ObjectManagerImp::~ObjectManagerImp()
{
	delete gameMan;
	
	// Destroy each object in the game
	for (size_t i{}; i < num_obj; i++) {
		destroyObject(i, true);
	}

	// Free each manager
	delete roomMan;
	delete textMan;
}





//--------------------------------------------------
//  ObjectManagerImp::Update() : .
//--------------------------------------------------
bool ObjectManagerImp::Update() {
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





//--------------------------------------------------
//  ObjectManagerImp::Draw() : .
//--------------------------------------------------
void ObjectManagerImp::Draw() {
	for (size_t i{}; i < num_obj; i++) {
		auto* obj = obj_array[i];
		if (obj) {
			obj->draw();
		}
	}
}





//--------------------------------------------------
//  ObjectManagerImp::CreateObject() : .
//--------------------------------------------------
size_t ObjectManagerImp::CreateObject(Object* obj)
{
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





//--------------------------------------------------
//  ObjectManagerImp::DestroyObject() : .
//--------------------------------------------------
void ObjectManagerImp::DestroyObject(size_t index, bool room_end)
{
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





//--------------------------------------------------
//  ObjectManagerImp::NextRoom() : .
//--------------------------------------------------
void ObjectManagerImp::NextRoom()
{
	if (roomMan->getCurrentRoom() < roomMan->getNumRooms()-1) {
		Room* room = roomMan->getRoomPointer(roomMan->getCurrentRoom());

		// Destroy every object in the room
		for (size_t i{}; i < room->getNumObjs(); i++) {
			destroyObject(*room->getObjectIndexFromArray(0),true);
		}
	}
	else game_end = true; // Trying to go the next room when no more exists ends the game
}





//--------------------------------------------------
//  ObjectManagerImp::GotoRoom() : .
//--------------------------------------------------
void ObjectManagerImp::GotoRoom(const char* name)
{
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





//--------------------------------------------------
//  ObjectManagerImp::RestartRoom() : .
//--------------------------------------------------
void ObjectManagerImp::RestartRoom()
{
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





//--------------------------------------------------
//  ObjectManagerImp::GetRenderer() : .
//--------------------------------------------------
SDL_Renderer* ObjectManagerImp::GetRenderer()
{
	return renderer;
}





//--------------------------------------------------
//  ObjectManagerImp::GetNumObj() : .
//--------------------------------------------------
size_t ObjectManagerImp::GetNumObj()
{
	return num_obj;
}





//--------------------------------------------------
//  ObjectManagerImp::GetObject() : .
//--------------------------------------------------
template<typename T>
T* ObjectManagerImp::GetObject(size_t index)
{
	if(index < num_obj) return dynamic_cast<T*>(obj_array[index]); // Type casts Object* to type of requested object. Can cause errors, watch out!
	return nullptr;
}





//--------------------------------------------------
//  ObjectManagerImp::InstanceFind() : .
//--------------------------------------------------
template<typename T>
T* ObjectManagerImp::InstanceFind(size_t num)
{
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





//--------------------------------------------------
//  ObjectManagerImp::InstanceList() : .
//--------------------------------------------------
template<typename T>
size_t ObjectManagerImp::InstanceList(size_t* arraytofill)
{
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
