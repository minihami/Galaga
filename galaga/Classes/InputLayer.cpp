#include "InputLayer.h"
#include "GameManager.h"

USING_NS_CC;

bool InputLayer::init()
{
	EventListenerKeyboard* keyInput = EventListenerKeyboard::create();
	keyInput->onKeyPressed = CC_CALLBACK_2(InputLayer::onKeyPressed, this);
	keyInput->onKeyReleased = CC_CALLBACK_2(InputLayer::onKeyReleased, this);
	
	/*register the event listener to the scene(?)*/
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyInput, this);
 
	return true;
}

void InputLayer::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event) 
{
	GameManager* pGM = (GameManager*)Director::getInstance()->getRunningScene()->getChildByTag(GM);
	if (pGM)
	{
		switch (keycode) 
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			pGM->leftSetter(true);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			pGM->rightSetter(true);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			pGM->fireSetter(true);
			break;
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			if (!(pGM->pauseGetter()))
				pGM->pauseSetter(true);
			break;
		default:
			break;
		}
	}
}


void InputLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) 
{
	GameManager* pGM = (GameManager*)Director::getInstance()->getRunningScene()->getChildByTag(GM);

	if (pGM)
	{
		switch (keycode) 
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			pGM->leftSetter(false);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			pGM->rightSetter(false);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			pGM->fireSetter(false);
			break;
		default:
			break;
		}
	}
}