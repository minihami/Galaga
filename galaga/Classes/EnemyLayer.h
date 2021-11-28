#pragma once

#include <cocos2d.h>
#include "Enemy.h"
#include "GameData.h"
#define ENEMY 0

class EnemyLayer : public cocos2d::Layer
{
public:

	virtual bool init();

	Enemy createEnemy(Vec2 position, int EnemyNumber);		/*create enemy and add to enemy layer*/
	Enemy createEnemy(Vec2 position, int EnemyNumber, int enemyLife);	/*create enemy with life and add to enemy layer*/
	void deadEnemy(int EnemyNumber);						/*remove enemy from the enemy layer*/

	CREATE_FUNC(EnemyLayer);

};