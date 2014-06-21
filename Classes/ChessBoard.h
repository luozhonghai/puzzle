#ifndef __CHESS_BOARD_H__
#define __CHESS_BOARD_H__ 

#include "cocos2d.h"
USING_NS_CC;
#include "ChessBall.h"


class ChessBoard : public CCLayer
{
public:

	~ChessBoard();

	CREATE_FUNC(ChessBoard);

	virtual bool init();

	bool initBoard(CCSize ccpSize);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);

	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	void chessMoveEnd(CCNode* pSender,void* pData);


	bool checkChessCancel();

	void chessCancelBySequence(float dt);

	void latentChessCancel(float dt);

	// cancel linked chess end notify
	void chessCancelEnd();

	void newBoardGenerate(float dt);
	
	// call from game layer: time end~
	void notifyRoundEnd();

	void latentRoundEnd(float dt);
private:

	CCSize _screenSize;

	CCSize _boardSize;

	CCSize _chessSize;

	//for selected chess
	float _chessYOffset;

	ChessBall * _pickedChess;
	ChessBall * _moveChess;

	//store chess (view)
	CCArray * _chessArray;

	//for render
	CCSpriteBatchNode * _gameBatchNode;

	//store chess(data)
	ChessCell _chessCell[6][6];

	ChessCell * _activeCell;

	EChessProperty getRandChessProperty();

	EChessProperty currentChessCheckProperty;
	//for cancel chess flag
	int visit[6][6];
	//sum of cancelled chess each colum
	int cancelCount[6];

	//score for single ball
	int singleCancelScore;
	// get bonus when cancel balls of multiple property in one touch
	int comboBonus;
	// property types for one touch
	int cancelTypes;
	//my local score
	int localScore;

	// relative with notifyRoundEnd
	bool _roundEnd;
	// ignore flag for end game when cancelling
	bool _cancelling;
};


#endif __CHESS_BOARD_H__