#include "PlayerLayer.h"
#include "EnemyLayer.h"
#include "InputLayer.h"
#include "BulletLayer.h"
#include "GameManager.h"
#include "UILayer.h"
#include "gameOverLayer.h"

USING_NS_CC;
using namespace std;
bool GameManager::init()					/*Game manager layer initialization*/
{
	/*variable initialization*/
	GameScore = 0;
	left = false;
	right = false;
	fire = false;
	pause = false;
	isGameOver = false;
	createEnemyBaseTimer = 1000;
	createEnemyCurrentTimer = createEnemyBaseTimer;
	totalCreatedEnemyCount = 0;
	playerLife = 3;
	enemyBulletCount = 100;
	bulletCount = 0;
	bulletDelayTimer = 20;
	bulletFireOn = bulletDelayTimer;

	return true;
}

/* When game start, initialization start situation */
void GameManager::StartInit()				
{
	createPlayer();							/*create player*/

	createEnemy();							/*create enemy*/

	scheduleUpdate();						/*update gamescene*/
}

/*create Player and add to player layer and player vector*/
void GameManager::createPlayer()			
{
	PlayerLayer *p_layer = (PlayerLayer*)Director::getInstance()->getRunningScene()->getChildByTag(PLAYER_LAYER);		/*get Player layer from the game scene*/
	if (p_layer) 
	{
		if (!p_layer->getChildByTag(PLAYER))
		{
			player.push_back(p_layer->createPlayer());	/*create player(add to player layer and add to player vector)*/
		}
	}
}

/*create Enemy and add to enemy layer and enemy vector*/
void GameManager::createEnemy()						
{
	srand(time(NULL));
	EnemyLayer *e_layer = (EnemyLayer*)Director::getInstance()->getRunningScene()->getChildByTag(ENEMY_LAYER);	/*get enemy layer from the game scene*/
	int enemyLifeSettingByEnemyCount;
	
	/*by the number of created enemy, enemy's life is increased*/
	if (totalCreatedEnemyCount < 8)
	{
		enemyLifeSettingByEnemyCount = 1;
	}
	else if (totalCreatedEnemyCount >= 8 && totalCreatedEnemyCount < 16)
	{
		enemyLifeSettingByEnemyCount = 2;
	}
	else if (totalCreatedEnemyCount >= 16 && totalCreatedEnemyCount < 24)
	{
		enemyLifeSettingByEnemyCount = 3;
	}
	else if (totalCreatedEnemyCount >= 24 && totalCreatedEnemyCount < 32)
	{
		enemyLifeSettingByEnemyCount = 4;
	}
	else if (totalCreatedEnemyCount >= 32)
	{
		enemyLifeSettingByEnemyCount = 5;
	}

	if (e_layer)
	{
		for (int x = 0; x < 8; x++)			/*create 8 enemys and add to enemy layer at (x, 700) */
		{
			enemy.push_back(e_layer->createEnemy(Vec2(60 + 50 * x, 700), totalCreatedEnemyCount, enemyLifeSettingByEnemyCount));
			totalCreatedEnemyCount++;
		}
	
		for (vector<Enemy>::iterator enemyIter= enemy.begin();  enemyIter != enemy.end(); ++enemyIter)	/* move all current enemy to downside (50 height) */
		{
			MoveBy* enemyMove = MoveBy::create(3.0, Vec2(0, -50));
			enemyIter->EnemySprite()->runAction(enemyMove);
		}
		if (totalCreatedEnemyCount > 10000) 
		{
			totalCreatedEnemyCount = 1000;
		}
	}
}

/*create player's bullet and add to bullet layer and player bullet vector*/
void GameManager::createBullet()		 
{
	BulletLayer *b_layer = (BulletLayer*)Director::getInstance()->getRunningScene()->getChildByTag(BULLET_LAYER);		/*get bullet layer from the game scene*/ 
	PlayerLayer *p_layer = (PlayerLayer*)Director::getInstance()->getRunningScene()->getChildByTag(PLAYER_LAYER);		/*get player layer from the game scene*/

	if (b_layer)						/*if bullet layer is exist*/
	{
		if (p_layer->getChildByTag(PLAYER))		/*if player in Player layer exist*/
		{
			Sprite* PlayerSprite = (Sprite*)p_layer->getChildByTag(PLAYER);		/*get player sprite*/
			Vec2 PlayerPosition = PlayerSprite->getPosition();					/*get player position*/
			playerBullet.push_back(b_layer->createBullet(Vec2(PlayerPosition.x, PlayerPosition.y + PlayerSprite->getContentSize().height), bulletCount)); /*create player's bullet and add to bullet layer and player's bullet vector*/
			bulletCount++;					/* bullet count increase */
			if (bulletCount > 20)			/*bullet Count initialization*/
				bulletCount = 0;
		}
	}
}

/*create enemy's bullet and add to bullet layer and enemy bullet vector*/
void GameManager::createEnemyBullet()
{
	BulletLayer *b_layer = (BulletLayer*)Director::getInstance()->getRunningScene()->getChildByTag(BULLET_LAYER);	/*get bullet layer from the game scene*/ 
	vector<Enemy>::iterator enemyIter;		/*vector Iterator to use check all enemy*/
	for (enemyIter = enemy.begin(); enemyIter != enemy.end(); ++enemyIter)
	{
		int fireTimer = enemyIter->getEnemyFireCurrentTimer();	/*get enemy's current fire timer*/
		fireTimer--;											/*and decrease fire timer*/
		if (fireTimer == 0)					/*if fireTimer == 0 , enemy fire the bullet*/
		{
			Vec2 EnemyPosition = enemyIter->getEnemyPosition();
			
			int baseTimer = enemyIter->getEnemyFireBaseTimer();
			enemyBullet.push_back(b_layer->createEnemyBullet(Vec2(EnemyPosition.x, (EnemyPosition.y - enemyIter->EnemySprite()->getContentSize().height)), enemyBulletCount));	/*create enemy's bullet and add to bullet layer and enemy's bullet vector*/
			enemyBulletCount++;
			enemyIter->setEnemyFireCurrentTimer(baseTimer);	/*set the enemy's current fire timer to original value(base timer)*/
			if (enemyBulletCount > 1000)
				enemyBulletCount = 100;
		}
		else				/*if fireTimer != 0, set the enemy's current timer to decreased fire timer*/
		{
			enemyIter->setEnemyFireCurrentTimer(fireTimer);
		}
	}
}

/*check if player's bullet and enemy is collided*/
void GameManager::checkEnemyBulletCollision()
{
	vector<Enemy>::iterator enemyIter;
	vector<Bullet>::iterator bulletIter;
	BulletLayer* b_layer = (BulletLayer*)Director::getInstance()->getRunningScene()->getChildByTag(BULLET_LAYER);
	EnemyLayer* e_layer = (EnemyLayer*)Director::getInstance()->getRunningScene()->getChildByTag(ENEMY_LAYER);
	UILayer* ui_layer = (UILayer*)Director::getInstance()->getRunningScene()->getChildByTag(UI_LAYER);

	bool enemyColisionFlag = false;

	for (enemyIter = enemy.begin(); enemyIter != enemy.end(); )
	{
		for (bulletIter = playerBullet.begin(); bulletIter != playerBullet.end(); )
		{
			Rect enemyRect = enemyIter->EnemySprite()->getBoundingBox();
			Rect bulletRect = bulletIter->BulletSprite()->getBoundingBox();
			if (bulletRect.intersectsRect(enemyRect))		/*if enemy collied by player bullet*/
			{
				b_layer->deadBullet(bulletIter->BulletSprite()->getTag());	/*remove the collied bullet from the bullet layer*/
				bulletIter = playerBullet.erase(bulletIter++);				/*remove the collied bullet from the bullet vector*/
				enemyColisionFlag = true;
				break;
			}
			else
			{
				++bulletIter;
			}
		}
		if (enemyColisionFlag)
		{
			int currentEnemyLife = enemyIter->enemyLifeGetter();	
			currentEnemyLife--;		
			if (currentEnemyLife == 0)	/*if enemy's life == 0, remove it*/
			{
				GameScore += enemyIter->enemyScoreGetter();		/*game score increased by the enemy score*/
				
				e_layer->deadEnemy(enemyIter->EnemySprite()->getTag());	/*remove the enemy from the enemy layer*/
				enemyIter = enemy.erase(enemyIter);			/*remove the enemy from the enemy vector*/
				
				if (ui_layer)		/*player's life modify*/
				{
					ui_layer->detachScore();
					ui_layer->setScore(GameScore);
				}
			}
			else			/*if enemy's life != 0, decrease enemy's life*/
			{
				enemyIter->enemyLifeSetter(currentEnemyLife);
			}
			enemyColisionFlag = false;
			break;
			
		}
		else
		{
			++enemyIter;
		}
	}

}

/*check if enemy's bullet and player is collided*/
void GameManager::checkPlayerBulletCollision()
{
	BulletLayer* b_layer = (BulletLayer*)Director::getInstance()->getRunningScene()->getChildByTag(BULLET_LAYER);
	PlayerLayer* p_layer = (PlayerLayer*)Director::getInstance()->getRunningScene()->getChildByTag(PLAYER_LAYER);
	UILayer* ui_layer = (UILayer*)Director::getInstance()->getRunningScene()->getChildByTag(UI_LAYER);

	bool playerCollisionFlag = false;	/*collison flag*/

	vector<Bullet>::iterator enemyBulletIter;
	if (!player.empty())
	{
		for (enemyBulletIter = enemyBullet.begin(); enemyBulletIter != enemyBullet.end(); ++enemyBulletIter)
		{
			Rect PlayerRect = player[0].PlayerSprite()->getBoundingBox();
			Rect enemyBulletRect = enemyBulletIter->BulletSprite()->getBoundingBox();

			if (PlayerRect.intersectsRect(enemyBulletRect))
			{
				playerCollisionFlag = true;
				break;
			}
		}

		if (playerCollisionFlag)
		{
			/*remove all enemy bullet from enemy layer*/
			for (enemyBulletIter = enemyBullet.begin(); enemyBulletIter != enemyBullet.end(); )
			{
				b_layer->deadBullet(enemyBulletIter->BulletSprite()->getTag());
				enemyBulletIter = enemyBullet.erase(enemyBulletIter++);
			}
			
			enemyBullet.clear();		/*remove all enemy bullet from enemy bullet vector*/
		
			p_layer->deadPlayer();		/*remove player from the player layer*/
			player.clear();				/*remove player from the player vector*/

			playerLife--;				/*decrease player's life*/
		
			ui_layer->detachLife();
			ui_layer->setLife(playerLife);	/*modify player life in UI layer*/

			if (playerLife == 0)			/* game over flag check*/
			{
				isGameOver = true;
			}
			else							/*life != 0, create new player to player layer and add to player vector*/
			{
				createPlayer();
			}
			playerCollisionFlag = false;

		}
	}
}

void GameManager::update(float delta)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	PlayerLayer* p_layer = (PlayerLayer*)Director::getInstance()->getRunningScene()->getChildByTag(PLAYER_LAYER);		/*get player layer from the game scene*/
	BulletLayer* b_layer = (BulletLayer*)Director::getInstance()->getRunningScene()->getChildByTag(BULLET_LAYER);		/*get bullet layer from the game scene*/
	
	
	createEnemyCurrentTimer--;				/*create enemy timer  decrease*/

	if(bulletFireOn>0)					/*bullet delay counter decrease*/
		bulletFireOn--;


	/*Player's command update*/
	if (p_layer)						/*if player layer exist*/
	{
		if(left)							/*command input : player move left*/
		{
			p_layer->movePlayerLeft();
		}
		
		else if(right)						/*command input : player move right*/
		{
			p_layer->movePlayerRight();
		}

		if (fire)							/*command input : player fire bullet*/
		{
			if (bulletFireOn == 0)	/*bulletFireOn(fire delay check) == 0 && not too many bullet */
			{
				createBullet();
				bulletFireOn = bulletDelayTimer;
			}
		}
		if (pause)							/*command input : puase the game by esc*/
		{
			/*create pause labels*/
			Label* resumeLabel = Label::create("resume", "fonts/godoRounded.ttf", 80);
			Label* returnLabel = Label::create("return to menu", "fonts/godoRounded.ttf", 80);
			Label* endGameLabel = Label::create("end game", "fonts/godoRounded.ttf", 80);
			
			/*make label react to appropriate callback function*/
			MenuItemLabel* pauseItem = MenuItemLabel::create(resumeLabel, CC_CALLBACK_1(GameManager::resumeLabelCallback, this));
			MenuItemLabel* returnItem = MenuItemLabel::create(returnLabel, CC_CALLBACK_1(GameManager::returnLabelCallback, this));
			MenuItemLabel* endGameItem = MenuItemLabel::create(endGameLabel, CC_CALLBACK_1(GameManager::endGameLabelCallback, this));
			
			/*create pause menu using created labels, allignment and set position*/
			Menu* pauseMenu = Menu::create(pauseItem, returnItem, endGameItem, NULL);
			pauseMenu->alignItemsVertically();
			pauseMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

			this->addChild(pauseMenu,20,"Pause");
			
			/*pause all enemy bullet action*/			
			for (vector<Bullet>::iterator bulletIter = enemyBullet.begin(); bulletIter != enemyBullet.end(); ++bulletIter)
			{
				bulletIter->BulletSprite()->stopAllActions();
			}
			/*pause all player bullet action*/
			for (vector<Bullet>::iterator bulletIter = playerBullet.begin(); bulletIter != playerBullet.end(); ++bulletIter)
			{
				bulletIter->BulletSprite()->stopAllActions();
			}
			/*pause gamemanager scheduler - no more player's command input*/
			this->pauseSchedulerAndActions();
			
		}
	}

	/*Enemy Creation event*/
	if (createEnemyCurrentTimer == 0 || enemy.size() == 0)			/* create enemy tiemr == 0 -> create enemy */
	{
		if(enemy.size()<20)						/*if the number of enemy is under 20, create new enemy*/
			createEnemy();
 		else                                    /*too many enemy exist, game over*/ 
		{
			isGameOver = true;
			p_layer->removeChildByTag(PLAYER);
			player.clear();
		}
		if(createEnemyBaseTimer > 300 )			/*if create enemy base counter is over 300, decrease the term of create new enemy*/
			createEnemyBaseTimer -= 30;
		createEnemyCurrentTimer = createEnemyBaseTimer;		/*set create new enemy counter = create enemy base counter*/
	}

	
	/*Enemy and player Bullet collision flag*/
	if (!playerBullet.empty() && !enemy.empty())	/*if player bullet and enemy is exist*/
	{
		checkEnemyBulletCollision();
	}

	/*player and enemy bullet collision flag*/
	if (!player.empty() && !enemyBullet.empty())		/*if enemy bullet and player is exist*/
	{
		checkPlayerBulletCollision();
	}

	/*Enemy Fire event*/
	createEnemyBullet();

	/*Bullet dead event*/
	if (b_layer)
	{
		/* check all player bullet if they are over the window upper side*/
		for (vector<Bullet>::iterator bulletIter = playerBullet.begin(); bulletIter != playerBullet.end(); )
		{
			if (bulletIter->getBulletPosition().y >= visibleSize.height)	/*player bullet is over the window, remove it from the bullet layer and player bullet vector*/
			{
				b_layer->deadBullet(bulletIter->BulletSprite()->getTag());
				bulletIter = playerBullet.erase(bulletIter++);
			}
			else
			{
				++bulletIter;
			}
		}
		/*check all enemy bullet if they are below the window's bottom*/
		for (vector<Bullet>::iterator enemyBulletIter = enemyBullet.begin(); enemyBulletIter != enemyBullet.end(); )
		{
			if (enemyBulletIter->getBulletPosition().y <= 0)		/*enemy bullet is below the window's bottom, remove it from the bullet layer and enemy bullet vector*/
			{
				b_layer->deadBullet(enemyBulletIter->BulletSprite()->getTag());
				enemyBulletIter = enemyBullet.erase(enemyBulletIter++);
			}
			else
			{
				++enemyBulletIter;
			}
		}
	}

	/*Game Over event*/
	if (isGameOver)
	{
		/*create Game over Layer*/
		gameOverLayer* gameover_layer = gameOverLayer::create();
		this->addChild(gameover_layer,10);
		isGameOver = false;
		this->pauseSchedulerAndActions();
	}

}

/*resume the game callback function*/
void GameManager::resumeLabelCallback(Object *sender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	/*give action to all enemy bullet to downside*/
	for (vector<Bullet>::iterator bulletIter = enemyBullet.begin(); bulletIter != enemyBullet.end(); ++bulletIter)
	{
		
		MoveBy *enemyBulletFire = MoveBy::create(2.0, Vec2(0, -visibleSize.height));
		bulletIter->BulletSprite()->runAction(enemyBulletFire);
	}
	/*give action to all player bullet to upside*/
	for (vector<Bullet>::iterator bulletIter = playerBullet.begin(); bulletIter != playerBullet.end(); ++bulletIter)
	{
		MoveBy *playerBulletFire = MoveBy::create(2.0, Vec2(0, visibleSize.height));
		bulletIter->BulletSprite()->runAction(playerBulletFire);
	}
	/*game manager scheduler resume - user command enable*/
	this->resumeSchedulerAndActions();

	/*remove pause menu*/
	this->removeChildByName("Pause");

	/*puase check initialized*/
	pause = false;
}

/*return to the menu callback function*/
void GameManager::returnLabelCallback(Object *sender)
{
	Director::getInstance()->popScene();	/*remove game scene and return to start scene*/
}

/*rendGame callback function*/
void GameManager::endGameLabelCallback(Object *sender)
{
	Director::getInstance()->end();		/*end the program*/
}