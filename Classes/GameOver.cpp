#include "GameOver.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOver::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create("GameOver.jpg", "GameOver.jpg", CC_CALLBACK_1(GameOver::menuBackToMain,this));
	closeItem->setTag(99);
	//closeItem->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
	closeItem->setPosition(Vec2(visibleSize.width/2,
		visibleSize.height/2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

void GameOver::menuBackToMain(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}