#pragma once

#include <cocos2d.h>
#include "Bullet.h"

class BulletLayer : public cocos2d::Layer
{
public:

	virtual bool init();

	Bullet createBullet(Vec2 Position, int BulletNumber);		/*create bullet and add to bullet layer*/

	Bullet createEnemyBullet(Vec2 Position, int BulletNumber);	/*create enemy's bullet and add to bullet layer*/
	
	void deadBullet(int BulletNumber);							/*remove bullet from the bullet layer*/
	
	CREATE_FUNC(BulletLayer);

};