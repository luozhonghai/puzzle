#include "ChessBoard.h"
#include "time.h"

bool ChessBoard::init()
{
	if ( !CCNode::init() )
	{
		return false;
	}

	_screenSize = CCDirector::sharedDirector()->getWinSize();

	_chessArray = CCArray::createWithCapacity(36);
	_chessArray->retain();

	_activeCell = new ChessCell();
	//listen for touches
	this->setTouchEnabled(true);

	return true;

}

bool ChessBoard::initBoard(CCSize ccpSize)
{
	_boardSize = ccpSize;
	_chessSize = ccpSize / 6;
	_chessYOffset = _chessSize.height * 0.25f;

	float chessScale = _chessSize.width / 100.f;

	CCPoint chessOrigin;
	chessOrigin.x = 70.f; //100
	chessOrigin.y = 50.f; // 35

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ball.plist");
	_gameBatchNode = CCSpriteBatchNode::create("ball.png");
	this->addChild(_gameBatchNode);

	ChessBall * chess;

	srand(time(0));
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			EChessProperty prop = getRandChessProperty();
			chess = ChessBall::createWithProperty(prop);
			chess->setScale(chessScale);
			chess->setPosition(chessOrigin + ccp(_chessSize.width * i, _chessSize.height * j));
			_gameBatchNode->addChild(chess);
			_chessArray->addObject(chess);

			_chessCell[i][j].pos = chessOrigin + ccp(_chessSize.width * i, _chessSize.height * j);
			_chessCell[i][j].ball = chess;
			chess->cell = &(_chessCell[i][j]);
		}
	}
	
	_moveChess = ChessBall::createWithProperty(ECP_Bear);
	_moveChess->cell = NULL;
	_moveChess->setScale(chessScale);
	_moveChess->setVisible(false);
	_gameBatchNode->addChild(_moveChess);

	_pickedChess = ChessBall::createWithProperty(ECP_Bear);
	_pickedChess->cell = NULL;
	_pickedChess->setScale(chessScale);
	_pickedChess->setVisible(false);
	_gameBatchNode->addChild(_pickedChess);
	
	memset(visit, 0, sizeof(visit));
	memset(cancelCount, 0, sizeof(cancelCount));
	return true;
}

ChessBoard::~ChessBoard()
{
	CC_SAFE_RELEASE(_chessArray);
}

void ChessBoard::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	int count;
	CCSetIterator i;
	ChessBall* sprite;
	CCTouch* touch;
	CCPoint tap;

	count = _chessArray->count();


	for (i = pTouches->begin(); i != pTouches->end(); i++)
	{
		touch = (CCTouch*) (*i);
		if (touch != NULL )
		{
			tap = touch->getLocation();
			for (int j = 0; j < count; j++)
			{
				sprite = (ChessBall*)_chessArray->objectAtIndex(j);
				if (sprite->boundingBox().containsPoint(tap))
				{			
					sprite->setOpacity(128);
					_activeCell->ball = sprite;
					_pickedChess->setVisible(true);
					_pickedChess->setPositionX(tap.x);
					_pickedChess->setPositionY(tap.y + _chessYOffset);
					_pickedChess->setChessProperty(sprite->getChessProperty());
					
				}
			}
		}
	}

}

void ChessBoard::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCPoint pos;
	CCSetIterator i;
	CCTouch* touch;
	ChessBall* sprite;
	int count = _chessArray->count();

	for (i = pTouches->begin(); i != pTouches->end(); i++)
	{
		touch = (CCTouch*)(*i);
		if (touch != NULL)
		{
			pos = touch->getLocation();
			_pickedChess->setPositionX(pos.x);
			_pickedChess->setPositionY(pos.y + _chessYOffset);

			for (int j = 0; j < count; j++)
			{
				sprite = (ChessBall*)_chessArray->objectAtIndex(j);
				if (sprite->boundingBox().containsPoint(pos))
				{
				//	sprite->setOpacity(128);
					if (_activeCell->ball != sprite)
					{
						CCMoveTo * move = CCMoveTo::create(0.1f, _activeCell->ball->getPosition());
						CCCallFuncND * end = CCCallFuncND::create(this, callfuncND_selector(ChessBoard::chessMoveEnd), _activeCell->ball);
						CCAction * action = CCSequence::create(move, end,NULL);
						_moveChess->setVisible(true);
						_moveChess->setChessProperty(sprite->getChessProperty());
						_moveChess->setPosition(sprite->getPosition());
						_moveChess->runAction(action);

						_activeCell->ball->setOpacity(0);
						_activeCell->ball->setChessProperty(sprite->getChessProperty());

						_activeCell->ball = sprite;
						_activeCell->ball->setOpacity(128);
						_activeCell->ball->setChessProperty(_pickedChess->getChessProperty());
					}
				}
			}
		}
	}
	
}

void ChessBoard::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	if (_pickedChess)
	{
		_pickedChess->setVisible(false);
		_activeCell->ball->setOpacity(255);
	}

	if (checkChessCancel())
	{
		//disable touches
		this->setTouchEnabled(false);
		scheduleOnce(schedule_selector(ChessBoard::chessCancelEnd), 0.55f);
	}
	else
	{
		//enable touches
		this->setTouchEnabled(true);
	}
}

void ChessBoard::chessMoveEnd(CCNode* pSender, void* pData)
{
	ChessBall * ball = (ChessBall*)pData;
	if (ball)
	{
		ball->setOpacity(255);
		_moveChess->setVisible(false);
	}
}

EChessProperty ChessBoard::getRandChessProperty()
{
	
	EChessProperty prop = (EChessProperty) (rand() % 6);
	return prop;
}

bool ChessBoard::checkChessCancel()
{
	int i, j = 0;
	bool findCancel = false;

	for (i = 0; i < 6; i ++)
	{
		for (j = 0; j < 4; j++)
		{
			if (_chessCell[i][j].ball->getChessProperty() == _chessCell[i][j + 1].ball->getChessProperty()
				&& _chessCell[i][j].ball->getChessProperty() == _chessCell[i][j + 2].ball->getChessProperty())
			{
				visit[i][j] = 1;
				visit[i][j+1] = 1;
				visit[i][j+2] = 1;
			}			
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 6; j++)
		{
			if (_chessCell[i][j].ball->getChessProperty() == _chessCell[i+1][j].ball->getChessProperty()
				&& _chessCell[i][j].ball->getChessProperty() == _chessCell[i+2][j].ball->getChessProperty())
			{
				visit[i][j] = 1;
				visit[i+1][j] = 1;
				visit[i+2][j] = 1;
			}
		}
	}

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			if (visit[i][j] == 1)
			{
				findCancel = true;
				CCFadeTo * fade = CCFadeTo::create(0.5f, 0);
				CCAction * action = CCSequence::create(fade, NULL);
				_chessCell[i][j].ball->runAction(action);

				cancelCount[i]++;
			}
		}
	}

	return findCancel;
}


void ChessBoard::chessCancelEnd(float dt)
{
	int lack = 0;
	int i, j;
	for (i = 0; i < 6; i++)
	{
		lack = 0;
		if (cancelCount[i] == 0)
		{
			continue;
		}

		for (j = 0; j < 6; j++)
		{
			if (visit[i][j] == 1)
			{
				lack++;
				_chessCell[i][j].ball->setPosition(ccp(_chessCell[i][j].pos.x, _chessCell[i][5].pos.y + lack * _chessSize.height));
				_chessCell[i][j].ball->setChessProperty(getRandChessProperty());
				
				int id = 5 - cancelCount[i] + lack;
				CCMoveTo * move = CCMoveTo::create(0.3f, _chessCell[i][id].pos); 
				CCFadeTo * fade = CCFadeTo::create(0.3f, 255);
				CCSpawn * moveFade = CCSpawn::create(move, fade, NULL);
				CCCallFuncND * end = CCCallFuncND::create(_chessCell[i][j].ball, callfuncND_selector(ChessBall::chessGenerateEnd), &(_chessCell[i][id]));
				CCAction * action = CCSequence::create(moveFade, end, NULL);
				_chessCell[i][j].ball->runAction(action);
				
			}
			else
			{
				int id = j - lack;
				CCMoveTo * move = CCMoveTo::create(0.3f, _chessCell[i][id].pos);
				CCCallFuncND * end = CCCallFuncND::create(_chessCell[i][j].ball, callfuncND_selector(ChessBall::chessGenerateEnd), &(_chessCell[i][id]));
				CCAction * action = CCSequence::create(move, end, NULL);
				_chessCell[i][j].ball->runAction(action);
			}
		}
	}

	memset(visit, 0, sizeof(visit));
	memset(cancelCount, 0, sizeof(cancelCount));

	scheduleOnce(schedule_selector(ChessBoard::newBoardGenerate), 0.35f);
}

void ChessBoard::newBoardGenerate(float dt)
{
	if (checkChessCancel())
	{
		//disable touches
		this->setTouchEnabled(false);
		scheduleOnce(schedule_selector(ChessBoard::chessCancelEnd), 0.55f);
	}
	else
	{
		//enable touches
		this->setTouchEnabled(true);
	}

}


