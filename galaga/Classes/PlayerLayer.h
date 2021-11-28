#pragma once

#include <cocos2d.h>
#include "Player.h"
#include "GameData.h"
#define PLAYER 0

class PlayerLayer : public cocos2d::Layer
{
public:


	virtual bool init();

	Player createPlayer();

	void movePlayerLeft();
	void movePlayerRight();
	void deadPlayer();

	
	CREATE_FUNC(PlayerLayer);


};