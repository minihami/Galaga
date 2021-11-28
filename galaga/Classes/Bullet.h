#pragma once
#include "cocos2d.h"

USING_NS_CC;
class Bullet
{
private:
	Sprite* bulletSprite = NULL;
public:
	Bullet(Vec2 position)										/*Bullet constructor*/
	{
		bulletSprite = Sprite::create("Bullet.png");
		bulletSprite->setPosition(position);
	}

	Vec2 getBulletPosition()									/*return the Bullet's position*/
	{									
		return bulletSprite->getPosition();
	}

	void setBulletPosition(Vec2 position)						/*setting Bullet's Position*/
	{
		bulletSprite->setPosition(position);
	}

	Sprite* BulletSprite()										/*return bullet's sprite*/
	{
		return bulletSprite;
	}
};
