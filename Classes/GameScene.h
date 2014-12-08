#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
#include "GameOver.h"
typedef enum {
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
}DIR_DEF;

class SnakeNode :public cocos2d::Ref
{
public:
	int row;
	int col;
	int dir;
	SnakeNode* preNode;
	cocos2d::Sprite* nodeSprite;
};

class GameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuBackToMain(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
	void logic(float t);
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	void endGame();

	bool selfCrash();
protected:
	SnakeNode* sHead;
	SnakeNode* sFood;
	cocos2d::Vector<SnakeNode*> allbody;


};



#endif // __GameScene_H__
