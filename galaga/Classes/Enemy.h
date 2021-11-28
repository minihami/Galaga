#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Enemy														/*Enemy class*/
{
private:
	Sprite* enemySprite =NULL;						
	int enemyLife = 1;					
	int enemyScore = 10;
	int enemyFireBaseTimer;					/*enemy fire base timer- randomly setted */
	int enemyFireCurrentTimer;
public:
	Enemy(Vec2 position)										/*Enemy constructor*/
	{
		Vec2 visibleSize = Director::getInstance()->getVisibleSize();
		enemyFireBaseTimer = rand() % 101 + 100;				
		enemyFireCurrentTimer = enemyFireBaseTimer;

		enemySprite = Sprite::create("Enemy.png");
		MoveTo* showupEnemy = MoveTo::create(3.0, position);
		enemySprite->setPosition(Vec2(position.x, visibleSize.y));
		enemySprite->runAction(showupEnemy);
		enemyLife = 1;
		enemyScore = 10;
	}
	Enemy(Vec2 position, int enemy_life)						/*Enemy constructor with enemy life*/
	{
		Vec2 visibleSize = Director::getInstance()->getVisibleSize();
		enemyFireBaseTimer = rand() % 101 + 100;
		enemyFireCurrentTimer = enemyFireBaseTimer;

		enemySprite = Sprite::create("Enemy.png");
		MoveTo* showupEnemy = MoveTo::create(3.0, position);
		enemySprite->setPosition(Vec2(position.x,visibleSize.y));
		enemySprite->runAction(showupEnemy);
		enemyLife = enemy_life;
		enemyScore = enemyLife * 10;
	}

	/*return the enemy's position*/
	Vec2 getEnemyPosition()										
	{									
		return enemySprite->getPosition();
	}
	
	/*setting Enemy's Position*/
	void setEnemyPosition(Vec2 position)						
	{
		enemySprite->setPosition(position);
	}

	/*return Enemy's Sprite*/
	Sprite* EnemySprite()										
	{
		return enemySprite;
	}

	/*return enemy's life*/
	int enemyLifeGetter()										
	{
		return enemyLife;
	}

	/*setting enemy's life*/
	void enemyLifeSetter(int enemylife)							
	{
		enemyLife = enemylife;
	}

	/*return enemy's Score*/
	int enemyScoreGetter()
	{
		return enemyScore;
	}

	/*return Enemy's current fire timer*/
	int getEnemyFireCurrentTimer()
	{
		return enemyFireCurrentTimer;
	}

	/*setting Enemy's current fire timer - when enemy fired, setting origial value(base timer)*/
	void setEnemyFireCurrentTimer(int setTimer)
	{
		enemyFireCurrentTimer = setTimer;
	}

	/*return enemy's base fire timer - use setting current fire timer to original value*/
	int getEnemyFireBaseTimer()
	{
		return enemyFireBaseTimer;
	}

};