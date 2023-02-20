#ifndef M2D_OBJECT_IH
#define M2D_OBJECT_IH

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DObject.h"

//--------------------------------------------------
//  Types
//--------------------------------------------------

class ObjectManager;

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace Obj
{

class ObjectImp : public Object
{
public:
	ObjectImp(ObjectManager* objMan, Room::Room* room, double X, double Y);
    ~ObjectImp();

    // Interface

    void Create();
	void Update();
	void EndUpdate();
	void Draw();
	void Destroy();
	double GetX();
	void SetX(double newx);
	double GetY();
	void SetY(double newy);
	void SetXY(double newx, double newy);
	void AddX(double add);
	void AddY(double add);
	double GetDirection();
	void SetDirection(double newdirection);
	SDL_Rect* GetColMask();
	bool SetSprite(std::string* path);
	bool GetHasSpr();
	const char* GetSpritePath();
	Spr::Sprite* GetSprite();
	void SetRoom(Room::Room* newroom);
	void SetRoomEnd();
	Room::Room* GetRoom();
	void SelfDestruct();
	bool GetPersistent();
	bool GetToDestruct();

    template<typename T>
    T* CheckCollision();

	size_t GetIndex();
	void SetIndex(size_t index);
    
private:
	ObjectManager* objMan;
    GameRoom::Room* room;
    bool persistent;
    bool room_end;
    size_t index;
    bool toDestruct;
    bool hasSpr;
    GameSpr::Sprite* spr;
    SDL_Rect col_mask;
    double x;
    double y;
    double direction;
};

}

#endif // M2D_OBJECT_IH