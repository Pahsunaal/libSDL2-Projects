#ifndef M2D_OBJECT_MANAGER_IH
#define M2D_OBJECT_MANAGER_IH

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include "M2DObjectManager.h"

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace Obj
{

class ObjectManagerImp : public ObjectManager
{
public:
	ObjectManagerImp(SDL_Renderer* renderer, IO::MouseInput* mouse, IO::KeyboardInput* keyboard);
	~ObjectManagerImp();

	// Interface

	bool Update();
	void Draw();
	SDL_Renderer* GetRenderer();
	size_t CreateObject(Object* obj);
	void DestroyObject(size_t index, bool room_end);
	void NextRoom();
	void GotoRoom(const char* name);
	void RestartRoom();
	size_t GetNumObj();

	template<typename T>
	T* GetObject(size_t index);

	template<typename T>
	T* InstanceFind(size_t num);

	template<typename T>
	size_t InstanceList(size_t* arraytofill);
private:
	Object* obj_array[max_obj];
	size_t num_obj;
	bool game_end;
	SDL_Renderer* renderer;
};

}

#endif // M2D_OBJECT_MANAGER_IH