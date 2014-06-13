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

	// cancel linked chess end notify
	void chessCancelEnd(float dt);

	void newBoardGenerate(float dt);
	
	bool checkChessCancel();
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

	//for cancel chess flag
	int visit[6][6];
	//sum of cancelled chess each colum
	int cancelCount[6];
};


#endif __CHESS_BOARD_H__