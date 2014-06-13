#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__ 


#include "cocos2d.h"
#include "ChessBoard.h"

class GameLayer : public cocos2d::CCLayer
{
public:

	ChessBoard * m_board;

	~GameLayer();
	// Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
	virtual bool init();
	// there's no 'id' in cpp, so we recommend to return the class instance pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(GameLayer);

	virtual void update(float delta);

	void createChessBoard();

	void createHud();

	void menuCloseCallback(CCObject* pSender);
	//input 
private:

	CCSize _screenSize;


	
};

#endif // __GAMELAYER_H__