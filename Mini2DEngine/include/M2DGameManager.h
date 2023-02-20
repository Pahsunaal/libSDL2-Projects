#ifndef M2D_GAME_MANAGER_H
#define M2D_GAME_MANAGER_H

/**
* @file M2DGameManager.h
* @brief The object that will begin every game
***************************************************/

//--------------------------------------------------
//  Class Declaration
//--------------------------------------------------

namespace Game
{

/** Setup and load main game stuff, rooms etc */
class GameManager
{
public:
	GameManager(ObjectManager* objMan) {};
	~GameManager() {};
};

}

#endif // M2D_GAME_MANAGER_H