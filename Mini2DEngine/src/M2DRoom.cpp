//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DRoomImp.h"
#include "M2DUtilitiesImp.h"

//--------------------------------------------------
//  Types
//--------------------------------------------------

using namespace Rm;
using namespace rapidjson;
using namespace Utils;





//--------------------------------------------------
//  RoomImp::RoomImp() : .
//--------------------------------------------------
RoomImp::RoomImp(std::string* room_path,
				 std::function<void(Room*)> creationCode,
				 Document* document,
				 RoomManager* roomMan)
				 :
				 path{ room_path },
				 creationCode { creationCode },
				 room_data{ document },
				 name{ (*document)["name"].GetString() },
				 obj_array{},
				 w{ (*document)["width"].GetInt() },
				 h{ (*document)["height"].GetInt() },
				 roomMan{ roomMan },
				 num_objs{}
{
}





//--------------------------------------------------
//  RoomImp::~RoomImp() : .
//--------------------------------------------------
RoomImp::~RoomImp()
{
	delete room_data;
	delete path;
}





//--------------------------------------------------
//  RoomImp::RoomStart() : .
//--------------------------------------------------
void RoomImp::RoomStart()
{
	//printf("Room start");
	creationCode(this);
}





//--------------------------------------------------
//  RoomImp::AddObject() : .
//--------------------------------------------------
bool RoomImp::AddObject(size_t* obj_index)
{
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





//--------------------------------------------------
//  RoomImp::RemoveObject() : .
//--------------------------------------------------
void RoomImp::RemoveObject(size_t* objToRemove)
{
	// Moves pointer if object found, but DOESN'T DELETE IT
	size_t delIndex{};
	for (size_t i{}; i < num_objs; i++) {
		if (*obj_array[i] == *objToRemove) {
			delIndex = i;
			break;
		}
	}

	// Moves other pointers fill space
	for (size_t i{ delIndex }; i < num_objs && i < max_room_obj-1; i++) {
		obj_array[i] = obj_array[i + 1];
	}
	obj_array[max_room_obj-1] = nullptr;
	num_objs--;
}





//--------------------------------------------------
//  RoomImp::GetObjectIndexFromArray() : .
//--------------------------------------------------
size_t* RoomImp::GetObjectIndexFromArray(size_t index)
{
	return obj_array[index];
}





//--------------------------------------------------
//  RoomImp::GetNumObjs() : .
//--------------------------------------------------
size_t RoomImp::GetNumObjs()
{
	return num_objs;
}





//--------------------------------------------------
//  RoomImp::GetName() : .
//--------------------------------------------------
std::string* RoomImp::GetName()
{
	return &name;
}





//--------------------------------------------------
//  RoomImp::GetWidth() : .
//--------------------------------------------------
int RoomImp::GetWidth()
{
	return w;
}





//--------------------------------------------------
//  RoomImp::GetHeight() : .
//--------------------------------------------------
int RoomImp::GetHeight()
{
	return h;
}





//--------------------------------------------------
//  RoomImp::GetPath() : .
//--------------------------------------------------
std::string* RoomImp::GetPath()
{
	return path;
}

#pragma endregion