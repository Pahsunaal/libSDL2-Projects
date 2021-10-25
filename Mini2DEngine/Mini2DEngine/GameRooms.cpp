#include "GameRooms.h"
#include "Utilities.h"


using namespace GameRoom;
using namespace rapidjson;
using namespace Utils;

#pragma region RoomManager

RoomManager::RoomManager() : current_room{}, room_array{}, room_names{}, num_rooms{} {
	printf("Created the roomManager\n");
}

RoomManager::~RoomManager() {
	for (size_t i{current_room}; i < num_rooms; i++) {
		delete room_array[i];
		room_array[i] = nullptr;
	}
	printf("Destroyed the roomManager\n");
}

Room* RoomManager::getRoomPointer(size_t index) {
	return room_array[index];
}

size_t RoomManager::getCurrentRoom() {
	return current_room;
}

std::string* RoomManager::getRoomName(size_t index) {
	return room_array[index]->getName();
}

bool RoomManager::selectRoom(const char* name) {
	auto index = room_names.find(name);
	if (index != room_names.end()) {
		current_room = index->second;
		room_array[current_room]->roomStart();
	}
	return false;
}

bool RoomManager::destroyRoom() {
	delete room_array[current_room];
	current_room++;
	num_rooms--;
	if (num_rooms > 0) {
		room_array[current_room]->roomStart();
		return true;
	} else return false;
}

bool RoomManager::restartRoom() {
	Room* room = getRoomPointer(getCurrentRoom());
	std::string* path = new std::string(*(room->getPath()));
	auto func = room->creationCode;
	delete room_array[current_room];
	auto document = parseJSON((*path).c_str());
	room = new Room{ path, func, document, this };
	room_array[current_room] = room;
	room->roomStart();
	return true;
}

bool RoomManager::addRoom(std::string* roomJSON, std::function<void(Room*)> creationCode) {
	if (num_rooms < max_rooms) {
		auto document = parseJSON((*roomJSON).c_str());
		Room* room = new Room{ roomJSON, creationCode, document, this };

		room_array[num_rooms] = room;
		room_names.insert(std::pair<std::string, size_t>((*document)["name"].GetString(), num_rooms));
		num_rooms++;
		return true;
	} else {
		return false;
	}
}

size_t RoomManager::getNumRooms() {
	return num_rooms;
}

#pragma endregion

#pragma region Room

Room::Room(std::string* room_path, std::function<void(Room*)> creationCode, Document* document, RoomManager* roomMan) : path{ room_path }, creationCode { creationCode }, room_data{ document }, name{ (*document)["name"].GetString() }, obj_array{}, w{ (*document)["width"].GetInt() }, h{ (*document)["height"].GetInt() }, roomMan{ roomMan }, num_objs{} {
}

Room::~Room() {
	delete room_data;
	delete path;
}

void Room::roomStart() {
	//printf("Room start");
	creationCode(this);
}

bool Room::addObject(size_t* obj_index) {
	if (num_objs < max_room_obj) {
		obj_array[num_objs] = obj_index;
		num_objs++;
		printf("Added Obj to %s, now %d objs\n", name.c_str(), num_objs);
		return false;
	}
	else {
		return true;
	}
}

void Room::removeObject(size_t* objToRemove) {
	size_t delIndex{};
	for (size_t i{}; i < num_objs; i++) {
		if (*obj_array[i] == *objToRemove) {
			delIndex = i;
			break;
		}
	}

	for (size_t i{ delIndex }; i < num_objs && i < max_room_obj-1; i++) {
		obj_array[i] = obj_array[i + 1];
	}
	obj_array[max_room_obj-1] = nullptr;
	num_objs--;
}

size_t* Room::getObjectIndexFromArray(size_t index) {
	return obj_array[index];
}

size_t Room::getNumObjs() {
	return num_objs;
}

std::string* Room::getName() {
	return &name;
}

int Room::getWidth() {
	return w;
}

int Room::getHeight() {
	return h;
}

std::string* Room::getPath() {
	return path;
}

#pragma endregion