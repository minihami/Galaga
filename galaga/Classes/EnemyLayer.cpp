#include "EnemyLayer.h"
#include <cocos2d.h>

bool EnemyLayer::init()
{
	return true;
}

Enemy EnemyLayer::createEnemy(Vec2 position,int EnemyNumber)		/*create enemy and add to enemy layer*/
{
	Enemy e = Enemy(position);
	this->addChild(e.EnemySprite(),0,EnemyNumber);
	return e;
}

Enemy EnemyLayer::createEnemy(Vec2 position, int EnemyNumber, int enemyLife)	/*create enemy with life and add to enemy layer*/
{
	Enemy e = Enemy(position, enemyLife);
	this->addChild(e.EnemySprite(), 0, EnemyNumber);
	return e;
}

void EnemyLayer::deadEnemy(int EnemyNumber)							/*remove enemy from the enemy layer*/
{
	this->removeChildByTag(EnemyNumber);
}