#include "StartLayer.h"
#include "GameScene.h"
#include "ScoreBoardScene.h"

bool StartLayer::init()
{
	Vec2 visibleSize = Director::getInstance()->getVisibleSize();

	/*create galaga image and add to start layer*/
	Sprite* galagaImg = Sprite::create("start_img.png");
	galagaImg->setPosition(Vec2(visibleSize.x/2,visibleSize.y-(galagaImg->getContentSize().height*2)));
	this->addChild(galagaImg);

	/*Label create*/
	Label* start = Label::createWithTTF("START", "fonts/godoRounded.ttf", 64);
	Label* scoreBoard = Label::createWithTTF("SCORE BOARD", "fonts/godoRounded.ttf", 64);
	Label* quit = Label::createWithTTF("QUIT", "fonts/godoRounded.ttf", 64);
	
	/*item create*/
	MenuItemLabel* startItem = MenuItemLabel::create(start, CC_CALLBACK_1(StartLayer::startCallback,this));
	MenuItemLabel* scoreBoardItem = MenuItemLabel::create(scoreBoard, CC_CALLBACK_1(StartLayer::scoreboardCallback, this));
	MenuItemLabel* quitItem = MenuItemLabel::create(quit, CC_CALLBACK_1(StartLayer::quitCallback, this));
	
	/*create menu with menuitem*/
	Menu* menu = Menu::create(startItem, scoreBoardItem, quitItem, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(visibleSize.x / 2, visibleSize.y *2/5));
	this->addChild(menu);

	return true;
}

void StartLayer::startCallback(Object *sender)
{
	Scene* runningGameScene = GameScene::createScene();
	Director::getInstance()->pushScene(runningGameScene);
}

void StartLayer::scoreboardCallback(Object *sender)
{
	Scene* scoreboardScene = ScoreBoardScene::createScene();
	Director::getInstance()->pushScene(scoreboardScene);
}

void StartLayer::quitCallback(Object *sender)
{
	Director::getInstance()->end();
}