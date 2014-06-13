#include "ChessBall.h"

char* ChessBall::fileName[6] = { "bunny_1.png", "bear_1.png", "cat_1.png", "chook_1.png", "pig_1.png", "frog_1.png" };

ChessBall* ChessBall::createWithProperty(EChessProperty prop)
{
	ChessBall * ball = new ChessBall();
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName[prop]);
	if (ball && ball->initWithSpriteFrame(pFrame))
	{
		
		ball->autorelease();
		ball->_chessProperty = prop;
		return ball;
	}
	CC_SAFE_DELETE(ball);
	return NULL;
}

void ChessBall::setChessProperty(EChessProperty prop)
{
	char * loadName = fileName[prop];
	CCSpriteFrame * frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(loadName);
	this->setDisplayFrame(frame);
	_chessProperty = prop;
}

ChessBall::ChessBall()
{

}

void ChessBall::chessGenerateEnd(CCNode* pSender, void* pData)
{
	ChessCell * cell = (ChessCell*)pData;
	if (cell)
	{
		cell->ball = this;
		this->cell = cell;
	}
}
