#ifndef M2D_OBJECT_H
#define M2D_OBJECT_H

/**
* @file M2DObject.h
* @brief Represent a game object
***************************************************/

//--------------------------------------------------
//  Includes
//--------------------------------------------------

//--------------------------------------------------
//  Types
//--------------------------------------------------

class ObjectManager;
class Room;

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace Obj
{

/** A GameObject, the base unit on which all objects within a game are built on */
class Object {
public:
    /** Destroy an object. Overrideable, required for overriding Object.destroy() with the derived class. See GameObjects.cpp for an example (Asteroid) */
    virtual ~Object() = 0;

    /** The Create event of an object. Overrideable */
    virtual void Create() = 0;

    /** The Update event of an object. Overrideable */
    virtual void Update() = 0;

    /** The End update event of an object. Overrideable */
    virtual void EndUpdate() = 0;

    /** The Draw event of an object. Overrideable */
    virtual void Draw() = 0;

    /** The Destroy event of an object. Overrideable. Use in conjunction with an overriden ~Object() for derived classes */
    virtual void Destroy() = 0;

    /** Get the x position of the object in the room */
    virtual double GetX() = 0;

    /** Set the x position of the object
    * @param newx: the x value in the room 
    */
    virtual void SetX(double newx) = 0;

    /** Get the y position of the object in the room */
    virtual double GetY() = 0;

    /** Set the y position of the object
    * @param newx: the y value in the room
    */
    virtual void SetY(double newy) = 0;

    /** Set the x and y position of the object
    * @param newx: the x value in the room 
    * @param newx: the y value in the room
    */
    virtual void SetXY(double newx, double newy) = 0;

    /** Add a value to the x position of the object
    * @param add: the amount to add
    */
    virtual void AddX(double add) = 0;

    /** Add a value to the y position of the object
    * @param add: the amount to add
    */
    virtual void AddY(double add) = 0;

    /** Get the direction of the object in degrees (it's rotation) */
    virtual double GetDirection() = 0;

    /** Set the direction of the object
    * @param newdirection: the angle of direction
    */
    virtual void SetDirection(double newdirection) = 0;

    /** Return the collision mask of the object, which is based on its sprite data */
    virtual SDL_Rect* GetColMask() = 0;

    /** Set the sprite of the object
    * @param path: the path of the new sprite
    */
    virtual bool SetSprite(std::string* path) = 0;

    /** Return whether the object has a sprite */
    virtual bool GetHasSpr() = 0;

    /** Get the path to the object's sprite */
    virtual const char* GetSpritePath() = 0;

    /** Get a pointer to the object's sprite */
    virtual Spr::Sprite* GetSprite() = 0;

    /** Change to room the object is 'in'. This means which object array the object is in. This is set to nullptr for a persistent object that has lost its original room 
    * @param newroom: a pointer to the room
    */
    virtual void SetRoom(Room::Room* newroom) = 0;

    /** Set the room_end flag to true - this flag is helpful in indicating that an object should act differently depending on whether it is being destroyed as part of game code, or simply the room/game ending. It is important to set this appropriately */
    virtual void SetRoomEnd() = 0;

    /** Get a pointer to the room the object is tied to */
    virtual Room::Room* GetRoom() = 0;

    /** Trigger the object to destroy itself in the next update */
    virtual void SelfDestruct() = 0;

    /** Return whether the object is persistsent */
    virtual bool GetPersistent() = 0;

    /** Return whether the object is going to be destroyed in the next update */
    virtual bool GetToDestruct() = 0;

    /** Check if the object is colliding with an object of type T using both object's collision masks
    * @tparam T: the type of the GameObject to check for collisions with
    */
    template<typename T>
    virtual T* CheckCollision() = 0;

    virtual size_t GetIndex() = 0;
    
    virtual void SetIndex(size_t index) = 0;
protected:
    Object(){};
};

}

#endif // M2D_OBJECT_H