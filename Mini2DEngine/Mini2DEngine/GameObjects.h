#pragma once

/**
* @file GameObjects.h
* @brief Handle objects
***************************************************/

#include "GameSprites.h"
#include "IOHandlers.h"
#include "GameRooms.h"
#include "GameText.h"
#include <map>

namespace GameObj {
	/** The maximum number of objects that can exist concurrently */
	const size_t max_obj{ 100 };

	struct Object;
	
	struct GameManager;

	/** A management object that handles object lifespan, creation, and storage. It also connects the keyboard, mouse, renderer, text and room managers to allow GameObjects to access them */
	struct ObjectManager {
		ObjectManager(SDL_Renderer* renderer, IO::MouseInput* mouse, IO::KeyboardInput* keyboard);
		~ObjectManager();

		/** Calls update event for all GameObjects */
		bool update();

		/** Calls draw event for all GameObjects */
		void draw();

		/** Returns a pointer to the render target */
		SDL_Renderer* getRenderer();

		/** Connects a freshly created object to the ObjectManager and returns its index in the array of GameObjects 
		* @param obj: pointer to created game object
		*/
		size_t createObject(Object* obj);

		/** Destroys an object, free the relevant memory and calling its destroy() event
		* @param index: the index of the object to remove
		* @param room_end: flag to indicate if this is a room_end destruction - this effects memory management, only use true if you know what you're doing
		*/
		void destroyObject(size_t index, bool room_end);

		/** Goes to the next room. Use over RoomManager functions */
		void nextRoom();

		/** Go to a specified room 
		* @param name: the name of the room to go to
		*/
		void gotoRoom(const char* name);

		/** Restart the current room */
		void restartRoom();

		/** Get the number of objects in the game */
		size_t getNumObj();

		/** Get a pointer to an object in the given type based on it's index in the array 
		* @tparam T: the type of the GameObject to get a pointer to
		* @param index: the index of the object to get
		*/
		template<typename T>
		T* getObject(size_t index);

		/** Get a pointer to the nth object of the given type if it exists
		* @tparam T: the type of the GameObject to get a pointer to
		* @param num: the ordinal object to get (1st, 2nd etc)
		*/
		template<typename T>
		T* instance_find(size_t num);

		/** Fill a list with the indexes of objects of the given type, and return the size of the list
		* @tparam T: the type of the GameObject to get a list of
		* @param arrayToFill: a pointer to the array that will be filled
		*/
		template<typename T>
		size_t instance_list(size_t* arraytofill);

		IO::MouseInput* mouse;
		IO::KeyboardInput* keyboard;
		GameRoom::RoomManager* roomMan;
		GameText::TextManager* textMan;
	private:
		Object* obj_array[max_obj];
		size_t num_obj;
		bool game_end;
		SDL_Renderer* renderer;
		GameManager* gameMan;
		
	};

	/** A GameObject, the base unit on which all objects within a game are built on */
	struct Object {
		/** Constructs an Object, use within the class prototype of a derived class 
		* @param objMan: Pointer to the ObjectManager
		* @param room: pointer to the room that the object is in
		* @param X: the x value in the room that the object starts at
		* @param Y: the y value in the room that the object starts at
		*/
		Object(ObjectManager* objMan, GameRoom::Room* room, double X, double Y);

		/** Destroy an object. Overrideable, required for overriding Object.destroy() with the derived class. See GameObjects.cpp for an example (Asteroid) */
		virtual ~Object();

		/** The Create event of an object. Overrideable */
		virtual void create();

		/** The Update event of an object. Overrideable */
		virtual void update();

		/** The End update event of an object. Overrideable */
		virtual void endUpdate();

		/** The Draw event of an object. Overrideable */
		virtual void draw();

		/** The Destroy event of an object. Overrideable. Use in conjunction with an overriden ~Object() for derived classes */
		virtual void destroy();

		/** Get the x position of the object in the room */
		double getX();

		/** Set the x position of the object
		* @param newx: the x value in the room 
		*/
		void setX(double newx);

		/** Get the y position of the object in the room */
		double getY();

		/** Set the y position of the object
		* @param newx: the y value in the room
		*/
		void setY(double newy);

		/** Set the x and y position of the object
		* @param newx: the x value in the room 
		* @param newx: the y value in the room
		*/
		void setXY(double newx, double newy);

		/** Add a value to the x position of the object
		* @param add: the amount to add
		*/
		void addX(double add);

		/** Add a value to the y position of the object
		* @param add: the amount to add
		*/
		void addY(double add);

		/** Get the direction of the object in degrees (it's rotation) */
		double getDirection();

		/** Set the direction of the object
		* @param newdirection: the angle of direction
		*/
		void setDirection(double newdirection);

		/** Return the collision mask of the object, which is based on its sprite data */
		SDL_Rect* getColMask();

		/** Set the sprite of the object
		* @param path: the path of the new sprite
		*/
		bool setSprite(std::string* path);

		/** Return whether the object has a sprite */
		bool getHasSpr();

		/** Get the path to the object's sprite */
		const char* getSpritePath();

		/** Get a pointer to the object's sprite */
		GameSpr::Sprite* getSprite();

		/** Change to room the object is 'in'. This means which object array the object is in. This is set to nullptr for a persistent object that has lost its original room 
		* @param newroom: a pointer to the room
		*/
		void setRoom(GameRoom::Room* newroom);

		/** Set the room_end flag to true - this flag is helpful in indicating that an object should act differently depending on whether it is being destroyed as part of game code, or simply the room/game ending. It is important to set this appropriately */
		void setRoomEnd();

		/** Get a pointer to the room the object is tied to */
		GameRoom::Room* getRoom();

		/** Trigger the object to destroy itself in the next update */
		void selfDestruct();

		/** Return whether the object is persistsent */
		bool getPersistent();

		/** Return whether the object is going to be destroyed in the next update */
		bool getToDestruct();

		/** Check if the object is colliding with an object of type T using both object's collision masks
		* @tparam T: the type of the GameObject to check for collisions with
		*/
		template<typename T>
		T* check_collision();

		size_t index;
	protected:
		ObjectManager* objMan;
		GameRoom::Room* room;
		bool persistent;
		bool room_end;
	private:
		bool toDestruct;
		bool hasSpr;
		GameSpr::Sprite* spr;
		SDL_Rect col_mask;
		double x;
		double y;
		double direction;
		
	};

	/** The object that will begin every game - add rooms here */
	struct GameManager {
		GameManager(ObjectManager* objMan);

		~GameManager();
	};
}