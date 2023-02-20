//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DObjectManagerImp.h"
#include "M2DGameManagerImp.h"
#include "M2DObjectImp.h"
#include "M2DUtilitiesImp.h"
#include <stdexcept>

//--------------------------------------------------
//  Defines
//--------------------------------------------------

#define KEYBOARD objMan->keyboard
#define MOUSE objMan->mouse
#define TEXT objMan->textMan

//--------------------------------------------------
//  Types
//--------------------------------------------------

using namespace Obj;
using namespace Spr;
using namespace Room;
using namespace Txt;
using namespace IO;
using namespace std::string_literals;





//--------------------------------------------------
//  ObjectImp::ObjectImp() : .
//--------------------------------------------------
ObjectImp::ObjectImp(ObjectManager* objMan,
                     Room* room,
                     double X,
                     double Y)
                     :
                     spr{},
                     hasSpr{},
                     x{ X },
                     y{ Y },
                     objMan{ objMan },
                     persistent{},
                     room{ room },
                     toDestruct{},
                     direction{},
                     col_mask{},
                     room_end{}
{
	index = objMan->GetNumObj();
	toDestruct = room->AddObject(&index);
	
}





//--------------------------------------------------
//  ObjectImp::~ObjectImp() : .
//--------------------------------------------------
ObjectImp::~ObjectImp()
{
	if(spr) delete spr;
}





//--------------------------------------------------
//  ObjectImp::Create() : .
//--------------------------------------------------
void ObjectImp::Create()
{

}





//--------------------------------------------------
//  ObjectImp::Draw() : .
//--------------------------------------------------
void ObjectImp::Draw()
{
	if(hasSpr) spr->Draw(x,y,direction);
}





//--------------------------------------------------
//  ObjectImp::Update() : .
//--------------------------------------------------
void ObjectImp::Update()
{

}





//--------------------------------------------------
//  ObjectImp::EndUpdate() : .
//--------------------------------------------------
void ObjectImp::EndUpdate()
{

}





//--------------------------------------------------
//  ObjectImp::Destroy() : .
//--------------------------------------------------
void ObjectImp::Destroy()
{

}





//--------------------------------------------------
//  ObjectImp::GetX() : .
//--------------------------------------------------
double ObjectImp::GetX()
{
	return x;
}





//--------------------------------------------------
//  ObjectImp::SetX() : .
//--------------------------------------------------
void ObjectImp::SetX(double newx)
{
	x = newx;

	// Update collision mask position if it exists
	if (hasSpr) {
		rapidjson::Document* details = spr->GetSpriteDetails();

		col_mask.x = x - (*details)["x_offset"].GetInt() + (*details)["mask_left"].GetInt();
	}
}





//--------------------------------------------------
//  ObjectImp::GetY() : .
//--------------------------------------------------
double ObjectImp::GetY()
{
	return y;
}





//--------------------------------------------------
//  ObjectImp::SetY() : .
//--------------------------------------------------
void ObjectImp::SetY(double newy)
{
	y = newy;

	// Update collision mask position if it exists
	if (hasSpr) {
		rapidjson::Document* details = spr->GetSpriteDetails();

		col_mask.y = y - (*details)["y_offset"].GetInt() + (*details)["mask_top"].GetInt();
	}
}





//--------------------------------------------------
//  ObjectImp::SetXY() : .
//--------------------------------------------------
void ObjectImp::SetXY(double newx, double newy)
{
	x = newx;
	y = newy;

	// Update collision mask position if it exists
	if (hasSpr) {
		rapidjson::Document* details = spr->GetSpriteDetails();

		col_mask.x = x - (*details)["x_offset"].GetInt() + (*details)["mask_left"].GetInt();
		col_mask.y = y - (*details)["y_offset"].GetInt() + (*details)["mask_top"].GetInt();
	}
}





//--------------------------------------------------
//  ObjectImp::AddX() : .
//--------------------------------------------------
void ObjectImp::AddX(double add)
{
	x += add;

	// Update collision mask position if it exists
	if (hasSpr) {
		rapidjson::Document* details = spr->GetSpriteDetails();

		col_mask.x = x - (*details)["x_offset"].GetInt() + (*details)["mask_left"].GetInt();
	}
}





//--------------------------------------------------
//  ObjectImp::AddY() : .
//--------------------------------------------------
void ObjectImp::AddY(double add)
{
	y += add;

	// Update collision mask position if it exists
	if (hasSpr) {
		rapidjson::Document* details = spr->GetSpriteDetails();

		col_mask.y = y - (*details)["y_offset"].GetInt() + (*details)["mask_top"].GetInt();
	}
}





//--------------------------------------------------
//  ObjectImp::SetSprite() : .
//--------------------------------------------------
bool ObjectImp::SetSprite(std::string* name)
{
	SpriteImp* tmp = spr;

	// Determine path of sprite based on name and rigid structure
	std::string imgpath = "sprites\\" + *name + "\\" + *name + ".png";
	std::string detailspath = "sprites\\" + *name + "\\" + *name + ".json";
	
	try {
		spr = new SpriteImp{ name->c_str(), imgpath.c_str(), detailspath.c_str(), objMan->getRenderer() };
		if (tmp) delete tmp; // Frees the old sprite if it existed
		hasSpr = true;

		rapidjson::Document* details = spr->getSpriteDetails();

		// Update collision mask position
		col_mask.x = x - (*details)["x_offset"].GetInt() + (*details)["mask_left"].GetInt();
		col_mask.w = (*details)["mask_right"].GetInt() - (*details)["mask_left"].GetInt();
		col_mask.y = y - (*details)["y_offset"].GetInt() + (*details)["mask_top"].GetInt();
		col_mask.h = (*details)["mask_bottom"].GetInt() - (*details)["mask_top"].GetInt();

		return true;
	}
	catch (std::runtime_error e) {
		printf("Error loading sprite: %s", e.what());
		return false;
	}
}





//--------------------------------------------------
//  ObjectImp::GetDirection() : .
//--------------------------------------------------
double ObjectImp::GetDirection()
{
	return direction;
}





//--------------------------------------------------
//  ObjectImp::SetDirection() : .
//--------------------------------------------------
void ObjectImp::SetDirection(double newdirection)
{
	direction = newdirection;
}





//--------------------------------------------------
//  ObjectImp::GetSprite() : .
//--------------------------------------------------
Sprite* ObjectImp::GetSprite()
{
	return spr;
}





//--------------------------------------------------
//  ObjectImp::GetHasSpr() : .
//--------------------------------------------------
bool ObjectImp::GetHasSpr()
{
	return hasSpr;
}





//--------------------------------------------------
//  ObjectImp::GetSpritePath() : .
//--------------------------------------------------
const char* ObjectImp::GetSpritePath()
{
	return spr->GetPath();
}





//--------------------------------------------------
//  ObjectImp::SetRoom() : .
//--------------------------------------------------
void ObjectImp::SetRoom(Room* newroom)
{
	room = newroom;
}





//--------------------------------------------------
//  ObjectImp::SetRoomEnd() : .
//--------------------------------------------------
void ObjectImp::SetRoomEnd()
{
	room_end = true;
}





//--------------------------------------------------
//  ObjectImp::GetRoom() : .
//--------------------------------------------------
GameRoom::Room* ObjectImp::GetRoom()
{
	return room;
}





//--------------------------------------------------
//  ObjectImp::GetToDestruct() : .
//--------------------------------------------------
bool ObjectImp::GetToDestruct()
{
	return toDestruct;
}





//--------------------------------------------------
//  ObjectImp::GetPersistent() : .
//--------------------------------------------------
bool ObjectImp::GetPersistent()
{
	return persistent;
}





//--------------------------------------------------
//  ObjectImp::GetColMask() : .
//--------------------------------------------------
SDL_Rect* ObjectImp::GetColMask()
{
	return &col_mask;
}





//--------------------------------------------------
//  ObjectImp::SelfDestruct() : .
//--------------------------------------------------
void ObjectImp::SelfDestruct()
{
	toDestruct = true;
}





//--------------------------------------------------
//  ObjectImp::CheckCollision() : .
//--------------------------------------------------
template<typename T>
T* ObjectImp::CheckCollision()
{
	size_t arraytofill[max_obj]{};

	size_t num = objMan->instance_list<T>(arraytofill);

	// Checks for a rectangle intersection on the collision mask of the current object and each object of the requested type
	for (size_t i{}; i < num; i++) {
		T* obj = objMan->getObject<T>(arraytofill[i]);
		auto result = rectIntersect(&col_mask, obj->getColMask());
		if (result) {
			return obj;
		}
	}
	return nullptr;
}
