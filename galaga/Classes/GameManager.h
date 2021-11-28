#pragma once
#include <cocos2d.h>
#include "GameData.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include <vector>
using namespace std;

class GameManager : public cocos2d::Layer
{
private:

	/*game score value*/
	int GameScore = 0;

	/*changed bu input layer's keyboard event*/
	bool left = false;
	bool right = false;
	bool fire = false;
	bool pause = false;

	/*check game is over*/
	bool isGameOver = false;

	/*enemy creation timer data*/
	int createEnemyBaseTimer = 1000;
	int createEnemyCurrentTimer = createEnemyBaseTimer;

	/*Enemy Data*/	
	vector<Enemy> enemy;
	int totalCreatedEnemyCount = 0;	/*use enemy's tag - total createdEnemyCount is 0 to 10000*/

	/*Player Data*/
	vector<Player> player;
	int playerLife = 3;

	/*Bullet Data*/
	vector<Bullet> playerBullet;			/*player's bullet*/
	vector<Bullet> enemyBullet;		/*enemy's bullet*/

	int enemyBulletCount = 100;		/* use enemy bullet's tag - enemy bullet use 100 to 1000 */
	int bulletCount = 0;			/* use player bullet's tag - player bullet use 0 to 20*/
	int bulletDelayTimer = 20;		/* use to prevent user's continuous bullet fire */
	int bulletFireOn = bulletDelayTimer; /*when bulletFireOn == 0, user can fire the bullet. if player fired the bullet, set bulletFireOn to original value(BulletDelayTimer)*/

public:

	virtual bool init();

	void leftSetter(bool in) {
		left = in;

	}
	void rightSetter(bool in) {
		right = in;

	}
	void fireSetter(bool in) {
		fire = in;

	}
	void pauseSetter(bool in) {
		pause = in;

	}

	bool leftGetter() {
		return left;
	}
	bool rightGetter() {
		return right;
	}
	bool fireGetter() {
		return fire;
	}
	bool pauseGetter() {
		return pause;
	}

	int GameScoreGetter() 
	{
		return GameScore;
	}
	bool isGameOverGetter()
	{
		return isGameOver;
	}

	void createPlayer();		/*create Player and add to player layer*/

	void createEnemy();			/*create Enemy and add to enemy layer*/

	void createBullet();		/*create Player's bullet and add to bullet layer*/

	void createEnemyBullet();	/*create Enemy's bullet and add to bullet layer*/

	void checkEnemyBulletCollision();	/*check if player's bullet and enemy is collided*/

	void checkPlayerBulletCollision();	/*check if enemy's bullet and player is collided*/

	void StartInit();		/*after game manager is initialized, setting start situation*/

	virtual void update(float delta);
	CREATE_FUNC(GameManager);

	void resumeLabelCallback(Object *sender);	/* resume the game - when pause label clicked, call this function */
	void returnLabelCallback(Object *sender);	/* retuen to the start scene - when return to menu label clicked, call this function */
	void endGameLabelCallback(Object *sender);	/* end the game - when end game label clicked, call this function */

};