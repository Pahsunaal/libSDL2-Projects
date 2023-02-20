#ifndef M2D_ROOM_MANAGER_H
#define M2D_ROOM_MANAGER_H

/**
* @file M2DRoomManager.h
* @brief Manage rooms/levels
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

/** Maximum number of rooms */
const size_t max_rooms{ 100 };

namespace Rm
{

class Room;

/** A RoomManager object - stores the rooms, handles their lifetime, and manages movement between each room */
class RoomManager
{
public:
    /** Get the room manager object */
    static RoomManager* Get();

    /** Get a pointer to the room 
    * @param index: the index of the room in the room_array
    */
    virtual Room* GetRoomPointer(size_t index) = 0;

    /** Get the index of the current room */
    virtual size_t GetCurrentRoom() = 0;

    /** Get the name of a room */
    virtual std::string* GetRoomName(size_t index) = 0;
    
    /** Destroy a room safely */
    virtual bool DestroyRoom() = 0;

    /** Get the number of rooms in the game */
    virtual size_t GetNumRooms() = 0;

    /** Go to a specific room - use ObjectManager.gotoRoom() for a safer function 
    * @param name: name of the room to go to
    */
    virtual bool SelectRoom(const char* name) = 0;

    /** Restart a room - use ObjectManager.restartRoom() for a safer function */
    virtual bool RestartRoom() = 0;

    /** Create a new room safely 
    * 
    * @param room_path: the path to the rooms json property file
    * @param creationCode: a function that runs at the start of the room. Put objects to store in each room here
    */
    virtual bool AddRoom(std::string* roomJSON, std::function<void(Room*)> creationCode) = 0;
protected:
    RoomManager(){};
    ~RoomManager(){};
};

}

#endif // M2D_ROOM_MANAGER_H