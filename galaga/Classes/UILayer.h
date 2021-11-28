#pragma once

#include <cocos2d.h>

class UILayer : public cocos2d::Layer
{
public:

	virtual bool init();

	void setScore(int score);
	void detachScore();

	void setLife(int life);
	void detachLife();
	CREATE_FUNC(UILayer);

};