#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;


class GameScene : public cocos2d::Scene
{
private:
	bool m_isGameManagerInit = false;	/*check gamemanager is initialized*/

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(GameScene);
};

#endif