#include "GameLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
bool GameLayer::init()
{
	//super init
	if ( !CCLayer::init() )
	{
		return false;
	}

	
	//get screen size
	_screenSize = CCDirector::sharedDirector()->getWinSize();

	//create board place ball
	createChessBoard();

	//create Hud
	createHud();

	//listen for touches
	this->setTouchEnabled(true);

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("DoYouEverShine.mp3", true);

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

}

void GameLayer::createChessBoard()
{
	m_board = ChessBoard::create();
	m_board->initBoard(ccp(420.f, 420.f));
	this->addChild(m_board);


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
}

void GameLayer::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

