#include "PuzzlePiece.h"
#include "GameBoardScene.h"

using namespace cocos2d;
using namespace std;

PuzzlePiece::PuzzlePiece()
{
	//
}

PuzzlePiece::~PuzzlePiece() {}

PuzzlePiece* PuzzlePiece::create(const std::string& fileName)
{
	PuzzlePiece *pPuzzlePiece = new PuzzlePiece();
	if (pPuzzlePiece->initWithFile(fileName))
	{
		pPuzzlePiece->setPuzzleFileName(fileName);
		pPuzzlePiece->autorelease();
		return pPuzzlePiece;
	}
	CC_SAFE_DELETE(pPuzzlePiece);
	return NULL;
}

PuzzlePiece* PuzzlePiece::createWithTexture(Texture2D *texture)
{
	PuzzlePiece *pPuzzlePiece = new PuzzlePiece();
	if (pPuzzlePiece->initWithTexture(texture))
	{
		pPuzzlePiece->autorelease();		
		return pPuzzlePiece;
	}
	CC_SAFE_DELETE(pPuzzlePiece);
	return nullptr;
}

void PuzzlePiece::setPuzzleFileName(const std::string& fileName)
{
	this->fileName = fileName;
}

void PuzzlePiece::setPercent(int percent)
{
	this->percent = percent;
}

void PuzzlePiece::setNumberConvex(int number_convex) { this->number_convex = number_convex; }
int PuzzlePiece::getNumberConvex() { return this->number_convex; }
void PuzzlePiece::setConvex_X(int x_convex)	{ this->x_convex = x_convex; }
void PuzzlePiece::setConvex_Y(int y_convex)	{ this->y_convex = y_convex; }
int PuzzlePiece::getConvex_X() { return this->x_convex; }
int PuzzlePiece::getConvex_Y() { return this->y_convex; }

void PuzzlePiece::onEnter()
{
	Sprite::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(PuzzlePiece::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PuzzlePiece::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PuzzlePiece::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool PuzzlePiece::onTouchBegan(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Rect rect = target->getBoundingBox();
	if (rect.containsPoint(touch->getLocation()))
	{
		target->setOpacity(100);
		return true;
	}
	return false;
}

void PuzzlePiece::onTouchMoved(Touch* touch, Event* event)
{
	auto target = static_cast<PuzzlePiece*>(event->getCurrentTarget());
	target->setPosition(target->getPosition() + touch->getDelta());
}

void PuzzlePiece::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<PuzzlePiece*>(event->getCurrentTarget());
	target->setOpacity(255);
}


