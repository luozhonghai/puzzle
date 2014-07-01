#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "spine/Json.h"
#include <string>
#include <iostream>
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;
bool GameLayer::init()
{
	//super init
	if ( !CCLayer::init() )
	{
		return false;
	}
	//get screen size
	_screenSize = CCDirector::sharedDirector()->getWinSize();

	_running = false;

	//createBG
	createBG();
	//create Hud
	createHud();


	//listen for touches
	this->setTouchEnabled(true);

	m_board = NULL;
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("DoYouEverShine.mp3", true);


	return true;
}

CCScene* GameLayer::scene()
{
	CCScene* scene = CCScene::create();
	GameLayer* layer = GameLayer::create();

	// add "layer" to "scene"
	scene->addChild(layer);
	return scene;
}

GameLayer::~GameLayer()
{

}

void GameLayer::update(float delta)
{
	_timeRound -= delta;
	int timeLeft = int(_timeRound);
	CCString* value = CCString::createWithFormat("Time: %i", timeLeft);
	_timeDisplay->setString(value->getCString());

	if (timeLeft == 0)
	{
		m_board->notifyRoundEnd();
	}
}

void GameLayer::createChessBoard()
{
	m_board = ChessBoard::create();
	m_board->initBoard(ccp(_screenSize.width * 0.9, _screenSize.width * 0.9));//420
	this->addChild(m_board,0,100);


	//CCSpriteFrame* frame2 = [[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:@"Default.png"];
}

void GameLayer::createHud()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(GameLayer::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width / 2,
		visibleSize.height - pCloseItem->getContentSize().height / 2));

	/*
	CCMenuItemImage *pGetScoreItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(GameLayer::menuGetHighScoreCallback));

	pGetScoreItem->setPosition(ccp(origin.x + pCloseItem->getContentSize().width / 2,
		visibleSize.height - pCloseItem->getContentSize().height / 2));

	CCMenuItemImage *pSetScoreItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(GameLayer::menuSetScoreCallback));

	pSetScoreItem->setPosition(ccp(origin.x + pCloseItem->getContentSize().width / 2,
		visibleSize.height - 3* pCloseItem->getContentSize().height / 2));
	*/
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);


	CCLabelTTF* pLabel = CCLabelTTF::create("Ball Puzzle", "Arial", 32);
	// position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - pLabel->getContentSize().height));
	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	_newDisplay = CCLabelTTF::create
		("Tap to Start!","Arial", 32);
	_newDisplay->setPosition(ccp
		(_screenSize.width * 0.5f, _screenSize.height * 0.6));
	this->addChild(_newDisplay, 2);

	_stopDisplay = CCLabelTTF::create
		("Round End Tap to restart!", "Arial", 32);
	_stopDisplay->setPosition(ccp
		(_screenSize.width * 0.5f, _screenSize.height * 0.6));
	this->addChild(_stopDisplay, 2);
	_stopDisplay->setVisible(false);

	_scoreDisplay = CCLabelTTF::create
		("score: 0", "Arial",24);
	_scoreDisplay->setAnchorPoint(ccp(0, 0.5));
	_scoreDisplay->setPosition(ccp
		(_screenSize.width * 0.05f, _screenSize.height * 0.94f));
	this->addChild(_scoreDisplay);

	_highScoreDisplay = CCLabelTTF::create
		("top:", "Arial",24);
	_highScoreDisplay->setAnchorPoint(ccp(0, 0.5));
	_highScoreDisplay->setPosition(ccp
		(_screenSize.width * 0.05f, _screenSize.height * 0.84f));
	this->addChild(_highScoreDisplay);
    
	_timeDisplay = CCLabelTTF::create
		("Time:", "Arial", 24);
	_timeDisplay->setAnchorPoint(ccp(1, 0.5));
	_timeDisplay->setPosition(ccp
		(_screenSize.width * 0.95f, _screenSize.height * 0.94f));
	this->addChild(_timeDisplay);

}

void GameLayer::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameLayer::menuGetScoreCallback(CCObject* pSender)
{
	cocos2d::extension::CCHttpRequest* request = new cocos2d::extension::CCHttpRequest();
	string player = "lolo";

	string requestUrl = "192.168.1.101:3000/server/score/get.json/?player=" + player;
	//string requestUrl = "127.0.0.1:3000/server/highscore.json";
	//string requestUrl = "127.0.0.1:3000/server/score/set/?player=" + player + "&score=" + score_str.m_sString;
	request->setUrl(requestUrl.c_str());
	request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpGet);
	request->setTag("Test Get");
	request->setResponseCallback(this, httpresponse_selector(GameLayer::onHttpGetScoreCompleted));
	cocos2d::extension::CCHttpClient::getInstance()->send(request);
	request->release();
}

void GameLayer::onHttpGetScoreCompleted(CCHttpClient* client, CCHttpResponse* response)
{
	/*
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	*/
	if (!response)
	{
		return;
	}

	CCLog("response code: %d", response->getResponseCode());
	if (!response->isSucceed())
	{
		CCLog("response failed");
		CCLog("error buffer:%s", response->getErrorBuffer());
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	std::string infoStr = string(buffer->begin(), buffer->end());

	Json*  convert = Json_create(infoStr.c_str());
	Json* item = Json_getItem(convert, "score");
	int itemInfo = item->valueint;

	printf("Http response , name value:");
		cout << itemInfo << endl;
	printf("Http response , dump data:");
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		printf("%c", (*buffer)[i]);
	}
	_playerScore = itemInfo;
}

void GameLayer::menuSetScoreCallback(CCObject* pSender)
{
	cocos2d::extension::CCHttpRequest* request = new cocos2d::extension::CCHttpRequest();

	//string requestUrl = "127.0.0.1:3000/server/score/set/?player=" + player + "&score=" + score_str->m_sString;
	string requestUrl = "192.168.1.101:3000/server/score/set";
	request->setUrl(requestUrl.c_str());
	request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpPost);
	request->setTag("Test Set");

//	vector<string> headers;
//	headers.push_back("Content-Type: application/json; charset=utf-8");
//	request->setHeaders(headers);
	string player = "lolo";
	CCString *score_str = CCString::createWithFormat("%d", _playerScore);
	string dataStr = "player=" + player + "&score=" + score_str->getCString();
	const char* postData = dataStr.c_str();
	request->setRequestData(postData, strlen(postData));
	request->setResponseCallback(this, httpresponse_selector(GameLayer::onHttpSetScoreCompleted));
	cocos2d::extension::CCHttpClient::getInstance()->send(request);
	request->release();
}

void GameLayer::onHttpSetScoreCompleted(CCHttpClient* client, CCHttpResponse* response)
{
}

void GameLayer::updateLocalScore(int score)
{
	CCString* value = CCString::createWithFormat("score: %i", score);
	_scoreDisplay->setString(value->getCString());
	_playerScore = score;
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
  if (!_running)
  {
	  _running = true;
	  if (_newDisplay->isVisible())
	  {
		  _newDisplay->setVisible(false);
	  }
	  else if (_stopDisplay->isVisible())
	  {
		  _stopDisplay->setVisible(false);
	  }
	  restartGame();
	  return;
  }

}

void GameLayer::roundEnd()
{
	_running = false;
	_stopDisplay->setVisible(true);
	if (m_board != NULL)
	{
		this->removeChild(m_board);
		m_board = NULL;
	}
	this->unschedule(schedule_selector(GameLayer::update));

	getServerHighScore();
	_stopDisplay->setVisible(true);
	if (_highScore >= _playerScore)
	{
	//	CCString* value = CCString::createWithFormat();
		_stopDisplay->setString("Try again ? ");
	}
	else
	{
		_stopDisplay->setString("High score refreshed!");
	}
		updateLocalScoreToServer();
}

void GameLayer::restartGame()
{

	//create board place ball
	createChessBoard();
	//listen for touches
	m_board->setTouchEnabled(true);
	_timeRound = 60.0;

	_playerScore = 0;
	_scoreDisplay->setString("score: 0");
	//create main loop
	this->schedule(schedule_selector(GameLayer::update));
	getServerHighScore();
}

void GameLayer::getServerHighScore()
{
	menuGetHighScoreCallback(this);
}

void GameLayer::getLocalScoreFromServer()
{
	menuGetScoreCallback(this);
}

void GameLayer::updateLocalScoreToServer()
{
	menuSetScoreCallback(this);
}

void GameLayer::menuGetHighScoreCallback(CCObject* pSender)
{
	cocos2d::extension::CCHttpRequest* request = new cocos2d::extension::CCHttpRequest();
	//string requestUrl = "127.0.0.1:3000/server/score/get.json/?player=" + player;
	string requestUrl = "192.168.1.101:3000/server/highscore.json";
	//string requestUrl = "127.0.0.1:3000/server/score/set/?player=" + player + "&score=" + score_str.m_sString;
	request->setUrl(requestUrl.c_str());
	request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpGet);
	request->setTag("Test Get");
	request->setResponseCallback(this, httpresponse_selector(GameLayer::onHttpGetHighScoreCompleted));
	cocos2d::extension::CCHttpClient::getInstance()->send(request);
	request->release();
}

void GameLayer::onHttpGetHighScoreCompleted(CCHttpClient* client, CCHttpResponse* response)
{
	/*
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);*/
	if (!response)
	{
		return;
	}

	CCLog("response code: %d", response->getResponseCode());
	if (!response->isSucceed())
	{
		CCLog("response failed");
		CCLog("error buffer:%s", response->getErrorBuffer());
		_highScoreDisplay->setString("top: can't connect to server");
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	std::string infoStr = string(buffer->begin(), buffer->end());

	Json*  convert = Json_create(infoStr.c_str());
	Json* item = Json_getItem(convert, "score");
	int itemInfo = item->valueint;

	printf("Http response , name value:");
	cout << itemInfo << endl;
	printf("Http response , dump data:");
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		printf("%c", (*buffer)[i]);
	}
	//display the high score!!
	CCString* value = CCString::createWithFormat("Top: %i", itemInfo);
	_highScoreDisplay->setString(value->getCString());
	_highScore = itemInfo;
}

void GameLayer::createBG()
{
	CCSprite* bg = CCSprite::create("Scence_BG.png");
	this->addChild(bg);
	float scaleX = _screenSize.width / bg->getContentSize().width;
	float scaleY = _screenSize.height / bg->getContentSize().height;
	bg->setPosition(ccp( _screenSize.width * 0.5, _screenSize.height * 0.5));
	bg->setScaleX(scaleX);
	bg->setScaleY(scaleY);
}

