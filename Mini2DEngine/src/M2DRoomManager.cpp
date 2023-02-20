//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DRoomManagerImp.h"
#include "M2DRoomImp.h"
#include "M2DUtilitiesImp.h"

//--------------------------------------------------
//  Types
//--------------------------------------------------

using namespace Rm;
using namespace rapidjson;
using namespace Utils;





//--------------------------------------------------
//  RoomManagerImp::RoomManagerImp() : .
//--------------------------------------------------
RoomManagerImp::RoomManagerImp() : current_room{}, room_array{}, room_names{}, num_rooms{}
{
	printf("Created the roomManager\n");
}





//--------------------------------------------------
//  RoomManagerImp::~RoomManagerImp() : .
//--------------------------------------------------
RoomManagerImp::~RoomManagerImp()
{
	for (size_t i{current_room}; i < num_rooms; i++) {
		delete room_array[i];
		room_array[i] = nullptr;
	}
	printf("Destroyed the roomManager\n");
}





//--------------------------------------------------
//  RoomManagerImp::GetRoomPointer() : .
//--------------------------------------------------
Room* RoomManagerImp::GetRoomPointer(size_t index)
{
	return room_array[index];
}





//--------------------------------------------------
//  RoomManagerImp::GetCurrentRoom() : .
//--------------------------------------------------
size_t RoomManagerImp::GetCurrentRoom()
{
	return current_room;
}





//--------------------------------------------------
//  RoomManagerImp::GetRoomName() : .
//--------------------------------------------------
std::string* RoomManagerImp::GetRoomName(size_t index)
{
	return room_array[index]->GetName();
}





//--------------------------------------------------
//  RoomManagerImp::SelectRoom() : .
//--------------------------------------------------
bool RoomManagerImp::SelectRoom(const char* name)
{
	auto index = room_names.find(name); // Checks for the name in the room_names map
	if (index != room_names.end()) {
		// Start room
		current_room = index->second;
		room_array[current_room]->RoomStart();
	}
	return false;
}





//--------------------------------------------------
//  RoomManagerImp::DestroyRoom() : .
//--------------------------------------------------
bool RoomManagerImp::DestroyRoom()
{
	delete room_array[current_room]; // Free room
	current_room++;
	num_rooms--;
	if (num_rooms > 0) {
		room_array[current_room]->RoomStart(); // Start next room
		return true;
	} else return false; // End game otherwise
}





//--------------------------------------------------
//  RoomManagerImp::RestartRoom() : .
//--------------------------------------------------
bool RoomManagerImp::RestartRoom()
{
	RoomImp* room = static_cast<RoomImp*>(GetRoomPointer(GetCurrentRoom()));
	std::string* path = new std::string(*(room->GetPath()));
	auto func = room->GetCreationCode();
	delete room_array[current_room];
	auto document = parseJSON((*path).c_str()); // Parse json files of properties
	room = new RoomImp{ path, func, document, this }; //Create a fresh copy of the room
	room_array[current_room] = room;
	room->RoomStart();
	return true;
}





//--------------------------------------------------
//  RoomManagerImp::AddRoom() : .
//--------------------------------------------------
bool RoomManagerImp::AddRoom(std::string* roomJSON, std::function<void(Room*)> creationCode)
{
	if (num_rooms < max_rooms) {
		auto document = parseJSON((*roomJSON).c_str()); // Parse json files of properties
		RoomImp* room = new RoomImp{ roomJSON, creationCode, document, this }; 

		// Add room to RoomManagerImp array and map
		room_array[num_rooms] = room;
		room_names.insert(std::pair<std::string, size_t>((*document)["name"].GetString(), num_rooms));
		num_rooms++;
		return true;
	} else {
		return false;
	}
}





//--------------------------------------------------
//  RoomManagerImp::GetNumRooms() : .
//--------------------------------------------------
size_t RoomManagerImp::GetNumRooms()
{
	return num_rooms;
}
