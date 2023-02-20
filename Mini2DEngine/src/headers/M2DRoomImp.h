#ifndef M2D_ROOM_IH
#define M2D_ROOM_IH

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DRoom.h"

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace Rm
{

class RoomImp : public Room
{
public:
	RoomImp(std::string* room_path, std::function<void(Room*)> creationCode, rapidjson::Document* document, RoomManager* roomMan);
	~RoomImp();

	// Interface

	void RoomStart();
	bool AddObject(size_t* obj_index);
	void RemoveObject(size_t* objToSearch);
	size_t* GetObjectIndexFromArray(size_t index);
	size_t GetNumObjs();
	std::string* GetName();
	int GetWidth();
	int GetHeight();
	std::string* GetPath();
	void SetCreationCode(std::function<void(Room*)> creationCode);
	std::function<void(Room*)> GetCreationCode();

	// Engine

	void RunCreationCode();
private:
	int w;
	int h;
	RoomManager* roomMan;
	std::function<void(Room*)> creationCode;
	
	size_t* obj_array[max_room_obj];
	size_t num_objs;
	std::string name;
	std::string* path;
	rapidjson::Document* room_data;
};

}

#endif // M2D_ROOM_IH