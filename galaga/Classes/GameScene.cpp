#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "PlayerLayer.h"
#include "EnemyLayer.h"
#include "BulletLayer.h"
#include "BGLayer.h"
#include "UILayer.h"
#include "InputLayer.h"
#include "GameManager.h"
#include "GameData.h"

#define BG_LAYER 0
#define BULLET_LAYER 1
#define ENEMY_LAYER 2
#define PLAYER_LAYER 3
#define UI_LAYER 4
#define GM 5
#define INPUT_LAYER 6

Scene* GameScene::createScene()
{
	return GameScene::create();
	
}

bool GameScene::init()
{
	PlayerLayer* p_layer = PlayerLayer::create();
	EnemyLayer* e_layer = EnemyLayer::create();
	BulletLayer* b_layer = BulletLayer::create();
	BGLayer* bg_layer = BGLayer::create();
	UILayer* ui_layer = UILayer::create();
	InputLayer* i_layer = InputLayer::create();
	GameManager* gm = GameManager::create();

	this->addChild(bg_layer, BG_LAYER, BG_LAYER);
	this->addChild(p_layer, PLAYER_LAYER, PLAYER_LAYER);
	this->addChild(e_layer, ENEMY_LAYER, ENEMY_LAYER);
	this->addChild(b_layer, BULLET_LAYER, BULLET_LAYER);
	this->addChild(ui_layer, UI_LAYER, UI_LAYER);
	this->addChild(gm, GM, GM);
	this->addChild(i_layer, INPUT_LAYER, INPUT_LAYER);

	m_isGameManagerInit = false;

	scheduleUpdate();

	return true;
}

void GameScene::update(float delta)
{
	
	if (m_isGameManagerInit == false)	/*if gamemanager is initialized, game manager start to setting base situation*/
	{
		GameManager *pGM = (GameManager *)this->getChildByTag(GM);
		if (pGM)
		{
			pGM->StartInit();
			m_isGameManagerInit = true;
		}
	}
	
}
