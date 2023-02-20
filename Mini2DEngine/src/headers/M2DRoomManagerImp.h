#ifndef M2D_ROOM_MANAGER_IH
#define M2D_ROOM_MANAGER_IH

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DRoomManager.h"

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace Rm
{

class Room;
class RoomImp;

class RoomManagerImp : public RoomManager
{
public:
    RoomManagerImp();
    ~RoomManagerImp();

	// Interface

    Room* GetRoomPointer(size_t index);
    size_t GetCurrentRoom();
    std::string* GetRoomName(size_t index);
    bool DestroyRoom();
    size_t GetNumRooms();
    bool SelectRoom(const char* name);
    bool RestartRoom();
    bool AddRoom(std::string* roomJSON, std::function<void(Room*)> creationCode);
private:
    RoomImp* room_array[max_rooms];
    std::map<std::string, size_t> room_names;
    size_t current_room;
    size_t num_rooms;
};

}

#endif // M2D_ROOM_MANAGER_IH