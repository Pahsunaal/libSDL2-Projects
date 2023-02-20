#ifndef M2D_ROOM_H
#define M2D_ROOM_H

/**
* @file M2DRoom.h
* @brief Handle rooms/levels
***************************************************/

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include <string>
#include <map>
#include <functional>
#include <rapidjson/document.h>

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace Rm
{

/** Maximum number of objects per room */
const size_t max_room_obj{ 100 };

class RoomManager;

/** A Room object - essentially a level that contains objects, some create code, and a width and height */
class Room
{
public:
	/** Run creation code of room */
	virtual void RoomStart() = 0;

	/** Add an object to the room - Unneccessary. Creating objects with ObjectManager already handles this function.
	* @param obj_index: a pointer to the objects index in the obj_array of ObjectManager
	*/
	virtual bool AddObject(size_t* obj_index) = 0;

	/** Remove an object from the room - Unneccessary. Destroying objects with ObjectManager already handles this function.
	* @param objToSearch: a pointer to the objects index in the obj_array of ObjectManager
	*/
	virtual void RemoveObject(size_t* objToSearch) = 0;

	/** Return a pointer to an objects index in the obj_array of ObjectManager from the room
	* @param index: index in the room's array of object index pointers
	*/
	virtual size_t* GetObjectIndexFromArray(size_t index) = 0;

	/** Get number of objects in the room */
	virtual size_t GetNumObjs() = 0;

	/** Get name of the room */
	virtual std::string* GetName() = 0;

	/** Get width of the room */
	virtual int GetWidth() = 0;

	/** Get height of the room */
	virtual int GetHeight() = 0;

	/** Get path to the rooms json file */
	virtual std::string* GetPath() = 0;

	/** Set the code to be executed when the room is created */
	virtual void SetCreationCode(std::function<void(Room*)> creationCode) = 0;

	/** Get the code to be executed when the room is created */
	virtual std::function<void(Room*)> GetCreationCode() = 0;
protected:
	Room(){};
	~Room(){};
};

}

#endif // M2D_ROOM_H