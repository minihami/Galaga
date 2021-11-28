#pragma once
#include <cocos2d.h>

USING_NS_CC;

class StartLayer : public cocos2d::Layer
{
public:

	virtual bool init();

	CREATE_FUNC(StartLayer);
	void startCallback(Object *sender);
	void scoreboardCallback(Object *sender);
	void quitCallback(Object *sender);
};
