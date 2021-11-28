#include "ScoreBoardScene.h"
#include "SimpleAudioEngine.h"
#include "ScoreBoardUILayer.h"
#include "UserScoreLayer.h"

Scene* ScoreBoardScene::createScene()
{
	return ScoreBoardScene::create();

}
bool ScoreBoardScene::init()
{
	/*add scoreboard UI*/
	Layer* scoreUILayer = ScoreBoardUILayer::create();
	this->addChild(scoreUILayer);

	/*add users' score record layer*/
	Layer* scoreLayer = UserScoreLayer::create();
	this->addChild(scoreLayer,2,"SCORE_LAYER");

	return true;
}
