#include "GameScene.h"
#include "BGLayer.h"
USING_NS_CC;

bool BGLayer::init() 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();			/* Window Size */

	Sprite* bg1 = Sprite::create("BG.png");						
	bg1->setAnchorPoint(Vec2(0, 0));										/*Background anchor point setting  ( left downside = (0,0) ) */
	bg1->setPosition(Vec2(0, 0));											/*Background position setting (at window's (0,0) point setting) */
		
	Sprite* bg2 = Sprite::create("BG.png");
	bg2->setAnchorPoint(Vec2(0.0, 0.0));									/*Background anchor point setting  ( left downside = (0,0) ) */
	bg2->setPosition(Vec2(0.0, visibleSize.height));						/*Background position setting (at window's (0, window's height) point setting) */	

	
	this->addChild(bg1);													/*bg1 add to layer*/
	this->addChild(bg2);													/*bg2 add to layer*/
	
	auto move_bg = MoveTo::create(10.0f, Vec2(0, -visibleSize.height));		/*Move Background bottom to upside*/
	auto bg_origin = Place::create(Vec2(0.0, 0.0));							/*move backgroung to original position(0,0)*/
	auto bg_seq = Sequence::create(move_bg, bg_origin, NULL);				

	this->runAction(RepeatForever::create(bg_seq));							/*repeat action forever*/

	return true;
}