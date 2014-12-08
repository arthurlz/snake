#include "GameHelp.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* GameHelp::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameHelp::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameHelp::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto labelHelp = Label::create("please touch screen to play the game", "Arial", 18);
	labelHelp->setPosition(Point(visibleSize.width / 2, 280));
	labelHelp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	this->addChild(labelHelp);

	auto labelBack = Label::create("Main Menu", "Arial", 15);
	auto itemBack = MenuItemLabel::create(labelBack, CC_CALLBACK_1(GameHelp::menuBackToMain, this));
	itemBack->setPosition(Point(visibleSize.width / 2, 120));

	auto menu = Menu::create(itemBack, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	return true;
}


void GameHelp::menuBackToMain(Ref* pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
