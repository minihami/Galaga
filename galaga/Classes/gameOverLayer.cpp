#include "gameOverLayer.h"
#include <cocos2d.h>
#include "ScoreBoardScene.h"
#include "UserScoreLayer.h"
#include "GameManager.h"

#define BG_LAYER 0
#define BULLET_LAYER 1
#define ENEMY_LAYER 2
#define PLAYER_LAYER 3
#define UI_LAYER 4
#define GM 5
#define INPUT_LAYER 6

bool gameOverLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/*create game over label and menu*/
	Label* gameOver = Label::createWithTTF("GAME OVER", "fonts/godoRounded.ttf", 64);
	MenuItemLabel* gameOverItem = MenuItemLabel::create(gameOver, CC_CALLBACK_1(gameOverLayer::gameOverCallback, this));
	
	Menu* gameOverMenu = Menu::create(gameOverItem, NULL);
	gameOverMenu->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	this->addChild(gameOverMenu);

	return true;
}

void gameOverLayer::gameOverCallback(Object *sender)
{
	GameManager* pGM = (GameManager*)Director::getInstance()->getRunningScene()->getChildByTag(GM);

	Scene* scoreboardScene = ScoreBoardScene::createScene();	/*create score board scene*/

	UserScoreLayer* userScoreLayer = (UserScoreLayer*)scoreboardScene->getChildByName("SCORE_LAYER");
	
	/*input the game score to the user score layer in scoreboard scene*/
	userScoreLayer->getUserScore(pGM->GameScoreGetter());
	
	Director::getInstance()->replaceScene(scoreboardScene);		/*remove game scene and push scoreboard scene*/
}