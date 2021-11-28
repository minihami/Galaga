#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"

class PlayScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(PlayScene);
};

#endif // __HELLOWORLD_SCENE_H__
