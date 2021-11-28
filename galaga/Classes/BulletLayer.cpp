#include "BulletLayer.h"
#define ENEMY_BULLET 1
#define PLAYER_BULLET 2

bool BulletLayer::init()												/*bullet layer initialization*/ 
{

	return true;
}

Bullet BulletLayer::createBullet(Vec2 position, int BulletNumber)		/*create player bullet and add to bullet layer*/
{

	Size visibleSize = Director::getInstance()->getVisibleSize();		/*get window size*/
	
	Bullet playerBullet = Bullet(position);										/*bullet constructor call*/
	this->addChild(playerBullet.BulletSprite(), PLAYER_BULLET, BulletNumber);					/*bullet add to bullet layer*/
	MoveBy *BulletFire = MoveBy::create(1.0, Vec2(0, visibleSize.height));			/*move bullet from player position to window upside action*/
	playerBullet.BulletSprite()->runAction(BulletFire);

	return playerBullet;
}



Bullet BulletLayer::createEnemyBullet(Vec2 position, int BulletNumber)				/*create enemy bullet and add to bullet layer*/
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Bullet enemyBullet = Bullet(position);
	this->addChild(enemyBullet.BulletSprite(), ENEMY_BULLET, BulletNumber);			/*enemy bullet add to bullet layer*/
	MoveBy *BulletFire = MoveBy::create(2.0, Vec2(0, -visibleSize.height));			/*move enemy bullet from enemy position to window downside action*/
	enemyBullet.BulletSprite()->runAction(BulletFire);

	return enemyBullet;

}
void BulletLayer::deadBullet(int BulletNumber)							/*remove bullet from the bullet layer*/
{
	this->removeChildByTag(BulletNumber);
}