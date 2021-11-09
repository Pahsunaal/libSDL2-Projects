#pragma once

/**
* @file GameRooms.h
* @brief Handle rooms/levels
***************************************************/

#include <string>
#include <map>
#include <functional>
#include <rapidjson/document.h>

namespace GameRoom {
	/** Maximum number of objects per room */
	const size_t max_room_obj{ 100 };

	/** Maximum number of rooms */
	const size_t max_rooms{ 100 };

	struct RoomManager;

	/** A Room object - essentially a level that contains objects, some create code, and a width and height */
	struct Room {
		/**
		* Construct new Room object - use RoomManager.addRoom() for safer room creation!
		*
		* @param room_path: the path to the rooms json property file
		* @param creationCode: a function that runs at the start of the room. Put objects to store in each room here
		* @param document: A structured interpretation of the rooms json property file
		* @param roomMan: pointer to it's manager. Dependency injection
		*/
		Room(std::string* room_path, std::function<void(Room*)> creationCode, rapidjson::Document* document, RoomManager* roomMan);

		/** Destruct room. Use RoomManager.destroyRoom() for a safer function*/
		~Room();

		/** Run creation code of room */
		void roomStart();

		/** Add an object to the room - Unneccessary. Creating objects with ObjectManager already handles this function.
		* @param obj_index: a pointer to the objects index in the obj_array of ObjectManager
		*/
		bool addObject(size_t* obj_index);

		/** Remove an object from the room - Unneccessary. Destroying objects with ObjectManager already handles this function.
		* @param objToSearch: a pointer to the objects index in the obj_array of ObjectManager
		*/
		void removeObject(size_t* objToSearch);

		/** Return a pointer to an objects index in the obj_array of ObjectManager from the room
		* @param index: index in the room's array of object index pointers
		*/
		size_t* getObjectIndexFromArray(size_t index);

		/** Get number of objects in the room */
		size_t getNumObjs();

		/** Get name of the room */
		std::string* getName();

		/** Get width of the room */
		int getWidth();

		/** Get height of the room */
		int getHeight();

		/** Get path to the rooms json file */
		std::string* getPath();

		std::function<void(Room*)> creationCode;
	private:
		int w;
		int h;
		RoomManager* roomMan;
		
		size_t* obj_array[max_room_obj];
		size_t num_objs;
		std::string name;
		std::string* path;
		rapidjson::Document* room_data;
	};

	/** A RoomManager object - stores the rooms, handles their lifetime, and manages movement between each room */
	struct RoomManager {
		/** Construct a RoomManager object */
		RoomManager();
		/** Destruct a RoomManager object*/
		~RoomManager();

		/** Get a pointer to the room 
		* @param index: the index of the room in the room_array
		*/
		Room* getRoomPointer(size_t index);

		/** Get the index of the current room */
		size_t getCurrentRoom();

		/** Get the name of a room */
		std::string* getRoomName(size_t index);
		
		/** Destroy a room safely */
		bool destroyRoom();

		/** Get the number of rooms in the game */
		size_t getNumRooms();

		/** Go to a specific room - use ObjectManager.gotoRoom() for a safer function 
		* @param name: name of the room to go to
		*/
		bool selectRoom(const char* name);

		/** Restart a room - use ObjectManager.restartRoom() for a safer function */
		bool restartRoom();

		/** Create a new room safely 
		* 
		* @param room_path: the path to the rooms json property file
		* @param creationCode: a function that runs at the start of the room. Put objects to store in each room here
		*/
		bool addRoom(std::string* roomJSON, std::function<void(Room*)> creationCode);
	private:
		Room* room_array[max_rooms];
		std::map<std::string, size_t> room_names;
		size_t current_room;
		size_t num_rooms;
	};

	
}