#include "UILayer.h"
USING_NS_CC;

bool UILayer::init() {

	setScore(0);	/*setting score 0*/
	setLife(3);		/*stting player's life 3*/

	return true;
}

/*make score to UI layer*/
void UILayer::setScore(int scoreSetting)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Label *score = Label::createWithTTF("Score : ", "fonts/godoRounded.ttf", 32);
	score->setPosition(Vec2(origin.x + visibleSize.width / 8, origin.y + visibleSize.height - score->getContentSize().height));


	char* scoreBuff = (char*)malloc(sizeof(char) * 100000);
	sprintf(scoreBuff, "Score : %d", scoreSetting);
	
	score->setString(scoreBuff);	/*change the score's string*/
	this->addChild(score, 0, "ScoreName");

	free(scoreBuff);
}

/*remove the score from the UI layer*/
void UILayer::detachScore() {
	this->removeChildByName("ScoreName");
}

/*make user's life to UI layer*/
void UILayer::setLife(int lifeSetting)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Label *life = Label::createWithTTF("Life : ", "fonts/godoRounded.ttf", 32);
	life->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - life->getContentSize().height));
	

	char* lifeBuff = (char*)malloc(sizeof(char) * 100);
	sprintf(lifeBuff, "Life : %d", lifeSetting);
	
	life->setString(lifeBuff);
	this->addChild(life, 0, "LifeName");

	free(lifeBuff);
}

/*remove the user's life from the UI layer*/
void UILayer::detachLife()
{
	this->removeChildByName("LifeName");
}