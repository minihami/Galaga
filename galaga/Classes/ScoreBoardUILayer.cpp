#include "ScoreBoardUILayer.h"
#include "UserScoreLayer.h"

bool ScoreBoardUILayer::init()
{
	Vec2 visibleSize = Director::getInstance()->getVisibleSize();
	
	/*Label create*/
	Label* title = Label::createWithTTF("SCORE BOARD", "fonts/godoRounded.ttf", 100);
	title->setPosition(Vec2(visibleSize.x / 2, visibleSize.y - (title->getContentSize().height) + 10));
	Label* back = Label::createWithTTF("BACK", "fonts/godoRounded.ttf", 32);

	/*MenuItem created*/
	MenuItemLabel* backItem = MenuItemLabel::create(back, CC_CALLBACK_1(ScoreBoardUILayer::backToMenuCallback, this));

	/*menu created*/
	Menu* backMenu = Menu::create(backItem, NULL);
	backMenu->setPosition(visibleSize.x / 2, visibleSize.y / 13);
	
	/*add children to this layer*/
	this->addChild(title);
	this->addChild(backMenu);


	return true;
}
void ScoreBoardUILayer::backToMenuCallback(Object *sender)
{
	/*deallcate memory for user's name input*/
	UserScoreLayer *user_score_layer = (UserScoreLayer*)Director::getInstance()->getRunningScene()->getChildByName("SCORE_LAYER");
	user_score_layer->freeInputName();
	
	Director::getInstance()->popScene();
}
