#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "StartLayer.h"

Scene* StartScene::createScene()
{
	return StartScene::create();

}

bool StartScene::init()
{
	Layer* startLayer = StartLayer::create();
	
	this->addChild(startLayer);
	return true;
}
