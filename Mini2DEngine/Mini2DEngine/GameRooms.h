#pragma once

#include <string>
#include <map>
#include <functional>
#include <rapidjson/document.h>

namespace GameRoom {
	const size_t max_room_obj{ 100 };
	const size_t max_rooms{ 100 };

	struct RoomManager;

	struct Room {
		Room(std::function<void(Room*)> creationCode, rapidjson::Document* document, RoomManager* roomMan);
		~Room();
		void roomStart();
		bool addObject(size_t* obj_index);
		void removeObject(size_t* objToSearch);
		size_t* getObjectIndexFromArray(size_t index);
		size_t getNumObjs();
		std::string* getName();
	private:
		int w;
		int h;
		RoomManager* roomMan;
		std::function<void(Room*)> creationCode;
		size_t* obj_array[max_room_obj];
		size_t num_objs;
		std::string name;
		rapidjson::Document* room_data;
	};

	struct RoomManager {
		RoomManager();
		~RoomManager();
		Room* getRoomPointer(size_t index);
		size_t getCurrentRoom();
		std::string* getRoomName(size_t index);
		bool destroyRoom();
		size_t getNumRooms();
		bool selectRoom(const char* name);
		bool addRoom(std::string* roomJSON, std::function<void(Room*)> creationCode);
	private:
		Room* room_array[max_rooms];
		std::map<std::string, size_t> room_names;
		size_t current_room;
		size_t num_rooms;
	};

	
}