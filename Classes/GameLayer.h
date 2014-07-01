#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__ 


#include "cocos2d.h"
#include "ChessBoard.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;

class GameLayer : public cocos2d::CCLayer
{
public:
	ChessBoard* m_board;

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

	void createBG();

	void menuCloseCallback(CCObject* pSender);

	void menuGetScoreCallback(CCObject* pSender);

	void onHttpGetScoreCompleted(CCHttpClient* client, CCHttpResponse* response);

	void menuSetScoreCallback(CCObject* pSender);

	void onHttpSetScoreCompleted(CCHttpClient* client, CCHttpResponse* response);

	void menuGetHighScoreCallback(CCObject* pSender);

	void onHttpGetHighScoreCompleted(CCHttpClient* client, CCHttpResponse* response);

	void updateLocalScore(int score);

	//call from chessBoard
	void roundEnd();
	//input 
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	
	//server related
	void getServerHighScore();

	void getLocalScoreFromServer();

	void updateLocalScoreToServer();

private:

	CCSize _screenSize;

	CCLabelTTF * _scoreDisplay;

	CCLabelTTF * _highScoreDisplay;

	CCLabelTTF * _timeDisplay;

	CCLabelTTF * _newDisplay;

	CCLabelTTF * _stopDisplay;

	// seconds
	float _timeRound;

	bool _running;

	void restartGame();

	int _playerScore;

	int _highScore;
	
};

#endif // __GAMELAYER_H__