
#include "cocos2d.h"
#include "PlayerLayer.h"
#include "Player.h"



USING_NS_CC;

bool PlayerLayer::init() {

	return true;
}

/*create Player and add to player layer*/
Player PlayerLayer::createPlayer() {

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Player createdPlayer = Player(Vec2(visibleSize.width / 2, 0));

	MoveTo *showupAction = MoveTo::create(1.0, Vec2(visibleSize.width / 2, visibleSize.height / 10));
		
	this->addChild(createdPlayer.PlayerSprite(),0,PLAYER);
	createdPlayer.PlayerSprite()->runAction(showupAction);
	
	return createdPlayer;
}

/*move player's sprite 5 point to left */
void PlayerLayer::movePlayerLeft() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* playerSprite = (Sprite*)(this->getChildByTag(PLAYER));
	
	if (playerSprite)
	{
		Vec2 pPosition = playerSprite->getPosition();
		if (pPosition.x > playerSprite->getContentSize().width / 2)
		{
			playerSprite->setPosition(Vec2( pPosition.x -5, pPosition.y));
		}
	}
}

/*move player's sprite 5 point to right */
void PlayerLayer::movePlayerRight() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* playerSprite = (Sprite*)(this->getChildByTag(PLAYER));

	if (playerSprite)
	{
		Vec2 pPosition = playerSprite->getPosition();
		if (pPosition.x < visibleSize.width - playerSprite->getContentSize().width / 2)
		{
			playerSprite->setPosition(Vec2(pPosition.x + 5, pPosition.y));
		}
	}
}

/*remove player from the player layer*/
void PlayerLayer::deadPlayer() 
{
	this->removeChildByTag(PLAYER);
}


