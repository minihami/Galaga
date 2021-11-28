#pragma once
#include "cocos2d.h"

USING_NS_CC;


class Player
{
private:
Sprite* pSprite = NULL; 
public:

	Player(Vec2 position)								/*Player constructor*/
	{								
		pSprite = Sprite::create("Player.png");
		pSprite->setPosition(position);
	}

	Vec2 getPlayerPosition()							/*return the player's position*/
	{							
		return pSprite->getPosition();
	}

	void setPlayerPosition(Vec2 position)				/*setting Player's Position*/
	{
		
		pSprite->setPosition(position);
	}

	Sprite* PlayerSprite()								/*return the player's figure*/
	{						
		return pSprite;
	}
};
