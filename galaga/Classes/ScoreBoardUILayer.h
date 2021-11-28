#pragma once

#include <cocos2d.h>
USING_NS_CC;

class ScoreBoardUILayer : public cocos2d::Layer
{
public:

	virtual bool init();

	CREATE_FUNC(ScoreBoardUILayer);

	void backToMenuCallback(Object *sender);
};