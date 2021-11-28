#pragma once

#include <cocos2d.h>
USING_NS_CC;

#define BG_LAYER 0
#define BULLET_LAYER 1
#define ENEMY_LAYER 2
#define PLAYER_LAYER 3
#define UI_LAYER 4
#define GM 5
#define INPUT_LAYER 6


class InputLayer : public cocos2d::Layer
{
public:

	virtual bool init();
	

	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	CREATE_FUNC(InputLayer);

};