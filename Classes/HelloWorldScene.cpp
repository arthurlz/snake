#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto labelStart = Label::create("Start Game", "Arial", 24);
	auto labelHelp = Label::create("Game Help", "Arial", 24);
	auto labelExit = Label::create("ExitGame", "Arial", 24);

	auto startItem = MenuItemLabel::create(labelStart, CC_CALLBACK_1(HelloWorld::menuCallback, this));
	startItem->setTag(2);
	startItem->setPosition(Point(origin.x + visibleSize.width/2, origin.y + 200));

	auto helpItem = MenuItemLabel::create(labelHelp, CC_CALLBACK_1(HelloWorld::menuCallback, this));
	helpItem->setTag(3);
	helpItem->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + 150));

	auto exitItem = MenuItemLabel::create(labelExit, CC_CALLBACK_1(HelloWorld::menuCallback, this));
	exitItem->setTag(4);
	exitItem->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + 100));

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCallback, this));
	closeItem->setTag(5);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, startItem, exitItem, helpItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = LabelTTF::create("Snake", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("taeyeon.jpg");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	switch (((Node*)pSender)->getTag())
	{
	case 2:
		CCLOG("go to game");
		Director::getInstance()->replaceScene(GameScene::createScene());
		break;
	case 3:
		CCLOG("go to help");
		Director::getInstance()->replaceScene(GameHelp::createScene());
		break;
	case 4:
		Director::getInstance()->end();
	case 5:
		Director::getInstance()->end();
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
