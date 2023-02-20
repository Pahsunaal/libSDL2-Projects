#ifndef M2D_OBJECT_MANAGER_H
#define M2D_OBJECT_MANAGER_H

/**
* @file M2DObjectManager.h
* @brief Manages objects in the game
***************************************************/

//--------------------------------------------------
//  Includes
//--------------------------------------------------

#include <map>
#include <cstddef>

//--------------------------------------------------
//  Types
//--------------------------------------------------

class Object;
class GameManager;
class SDL_Renderer;

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace Obj
{

/** The maximum number of objects that can exist concurrently */
const size_t max_obj{ 100 };

/** A management object that handles object lifespan, creation, and storage. It also connects the keyboard, mouse, renderer, text and room managers to allow GameObjects to access them */
class ObjectManager
{
public:
	/** Get the object manager */
	static ObjectManager* Get();

	virtual ~ObjectManager() = 0;

	/** Calls update event for all GameObjects */
	virtual bool Update() = 0;

	/** Calls draw event for all GameObjects */
	virtual void Draw() = 0;

	/** Returns a pointer to the render target */
	virtual SDL_Renderer* GetRenderer() = 0;

	/** Connects a freshly created object to the ObjectManager and returns its index in the array of GameObjects 
	* @param obj: pointer to created game object
	*/
	virtual size_t CreateObject(Object* obj) = 0;

	/** Destroys an object, free the relevant memory and calling its destroy() event
	* @param index: the index of the object to remove
	* @param room_end: flag to indicate if this is a room_end destruction - this effects memory management, only use true if you know what you're doing
	*/
	virtual void DestroyObject(size_t index, bool room_end) = 0;

	/** Goes to the next room. Use over RoomManager functions */
	virtual void NextRoom() = 0;

	/** Go to a specified room 
	* @param name: the name of the room to go to
	*/
	virtual void GotoRoom(const char* name) = 0;

	/** Restart the current room */
	virtual void RestartRoom() = 0;

	/** Get the number of objects in the game */
	virtual size_t GetNumObj() = 0;

	/** Get a pointer to an object in the given type based on it's index in the array 
	* @tparam T: the type of the GameObject to get a pointer to
	* @param index: the index of the object to get
	*/
	template<typename T>
	virtual T* GetObject(size_t index) = 0;

	/** Get a pointer to the nth object of the given type if it exists
	* @tparam T: the type of the GameObject to get a pointer to
	* @param num: the ordinal object to get (1st, 2nd etc)
	*/
	template<typename T>
	virtual T* InstanceFind(size_t num) = 0;

	/** Fill a list with the indexes of objects of the given type, and return the size of the list
	* @tparam T: the type of the GameObject to get a list of
	* @param arrayToFill: a pointer to the array that will be filled
	*/
	template<typename T>
	virtual size_t InstanceList(size_t* arraytofill) = 0;
protected:
	ObjectManager(){};
};
}

#endif // M2D_OBJECT_MANAGER_H