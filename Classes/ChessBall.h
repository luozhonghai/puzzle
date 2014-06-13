#ifndef __CHESS_BALL_H__
#define __CHESS_BALL_H__

#include "cocos2d.h"
USING_NS_CC;

typedef enum 
{
	ECP_Bunny,
	ECP_Bear,
	ECP_Cat,
	ECP_Chook,
	ECP_Pig,
	ECP_Frog
}EChessProperty;

class ChessBall;
class ChessCell
{
public:
	CCPoint pos;
	ChessBall * ball;

private:

};

class ChessBall : public CCSprite
{
public:

	ChessCell* cell;


	ChessBall();
//	CC_SYNTHESIZE(EChessProperty, _chessProperty, ChessProperty);


	EChessProperty getChessProperty() const { return _chessProperty; }

	void setChessProperty(EChessProperty prop);

	static ChessBall* createWithProperty(EChessProperty prop);

	// generate new chess and chess fall end notify
	void chessGenerateEnd(CCNode* pSender, void* pData);

protected:
	EChessProperty _chessProperty;
private:

	static char* fileName[6];
};


#endif