#pragma once

#include <cocos2d.h>
USING_NS_CC;

class gameOverLayer : public cocos2d::Layer
{
public:

	virtual bool init();

	CREATE_FUNC(gameOverLayer);

	void gameOverCallback(Object *sender);	/*game over label callback function*/

};