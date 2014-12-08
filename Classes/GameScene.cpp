#include "GameScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->setKeyboardEnabled(true);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
		{
			Director::getInstance()->replaceScene(HelloWorld::createScene());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif
		}
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto labelBack = Label::create("Main Menu", "Arial", 15);
	auto itemBack = MenuItemLabel::create(labelBack, CC_CALLBACK_1(GameScene::menuBackToMain, this));
	itemBack->setPosition(Point(visibleSize.width, 0));
	itemBack->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);

	auto menu = Menu::create(itemBack, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	auto bkWall = Sprite::create("bk.jpg");
	bkWall->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bkWall);


	//snake node
	sHead = new SnakeNode();
	sHead->row = rand() % 10;
	sHead->col = rand() % 15;
	sHead->preNode = NULL;
	sHead->dir = NULL;


	sFood = new SnakeNode();
	sFood->row = rand() % 10;
	sFood->col = rand() % 15;

	auto snakeNode = Sprite::create("node_snake.png");
	snakeNode->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	snakeNode->setPosition(Point(sHead->col * 32, sHead->row * 32));
	sHead->nodeSprite = snakeNode;
	this->addChild(snakeNode);

	auto foodNode = Sprite::create("node_food.png");
	foodNode->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	foodNode->setPosition(Point(sFood->col * 32, sFood->row * 32));
	sFood->nodeSprite = foodNode;
	this->addChild(foodNode);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	this->schedule(SEL_SCHEDULE(&GameScene::logic), 0.5f);
	return true;
}


void GameScene::menuBackToMain(Ref* pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}


bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	Point touchPoint = touch->getLocation();
	int touchRow = ((int)touchPoint.y) / 32;
	int touchCol = ((int)touchPoint.x) / 32;

	if (abs(touchRow - sHead->row) > abs(touchCol - sHead->col))
	{
		if (touchRow > sHead->row)
		{
			if (sHead->dir != DIR_DEF::DOWN)
				sHead->dir = DIR_DEF::UP;
			
		}
		else
		{
			if (sHead->dir != DIR_DEF::UP)
				sHead->dir = DIR_DEF::DOWN;
		}
	}
	else
	{
		if (touchCol > sHead->col)
		{
			if (sHead->dir != DIR_DEF::LEFT)
				sHead->dir = DIR_DEF::RIGHT;
		}
		else
		{
			if (sHead->dir != DIR_DEF::RIGHT)
				sHead->dir = DIR_DEF::LEFT;
		}
	}

	return true;
}

void GameScene::logic(float t)
{
	for (int i = allbody.size() - 1; i >= 0; i--)
	{
		auto sn = allbody.at(i);
		sn->dir = sn->preNode->dir;
		sn->row = sn->preNode->row;
		sn->col = sn->preNode->col;
		sn->nodeSprite->setPosition(Point(sn->col * 32, sn->row * 32));
	}

	switch (sHead->dir)
	{
	case DIR_DEF::UP:
		sHead->row++;
		if (sHead->row > 11 || selfCrash())
		{
			endGame();
		}
		break;
	case DIR_DEF::DOWN:
		sHead->row--;
		if (sHead->row < 0 || selfCrash())
		{
			endGame();
		}
		break;
	case DIR_DEF::LEFT:
		sHead->col--;
		if (sHead->col < 0 || selfCrash())
		{
			endGame();
		}
		break;
	case DIR_DEF::RIGHT:
		sHead->col++;
		if (sHead->col > 15 || selfCrash())
		{
			endGame();
		}
		break;
	}
	sHead->nodeSprite->setPosition(Point(sHead->col * 32, sHead->row * 32));

	if (sHead->col == sFood->col && sHead->row == sFood->row)
	{
		sFood->row = rand() % 10;
		sFood->col = rand() % 15;
		sFood->nodeSprite->setPosition(Point(sFood->col * 32, sFood->row * 32));
		auto snakeNode = new SnakeNode();
		if (allbody.empty())
		{
			snakeNode->preNode = sHead;
		}
		else
		{
			snakeNode->preNode = allbody.back();
		}
		switch (snakeNode->preNode->dir)
		{
		case DIR_DEF::UP:
			snakeNode->row = snakeNode->preNode->row - 1;
			snakeNode->col = snakeNode->preNode->col;
			break;
		case DIR_DEF::DOWN:
			snakeNode->row = snakeNode->preNode->row + 1;
			snakeNode->col = snakeNode->preNode->col;
			break;
		case DIR_DEF::LEFT:
			snakeNode->row = snakeNode->preNode->row;
			snakeNode->col = snakeNode->preNode->col + 1;
			break;
		case DIR_DEF::RIGHT:
			snakeNode->row = snakeNode->preNode->row;
			snakeNode->col = snakeNode->preNode->col - 1;
			break;
		}

		auto nodeSprite = Sprite::create("node_snake.png");
		nodeSprite->setPosition(Point(snakeNode->col * 32, snakeNode->row * 32));
		nodeSprite->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		snakeNode->nodeSprite = nodeSprite;
		this->addChild(nodeSprite);

		allbody.pushBack(snakeNode);
	}

}

void GameScene::endGame()
{
	//Director::getInstance()->end();
	Director::getInstance()->replaceScene(GameOver::createScene());
}

bool GameScene::selfCrash()
{
	for (auto& a : allbody)
	{
		if (a->row == sHead->row && a->col == sHead->col)
		{
			return true;
		}
	}
	return false;
}