#include "GameBoardScene.h"
#include <iostream>

USING_NS_CC;

Scene* GameBoard::createScene()
{	
	auto scene = Scene::create();	
	auto layer = GameBoard::create();	
	scene->addChild(layer);	
	return scene;
}

bool GameBoard::init()
{	
	if (!Layer::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	createPuzzle();
	logic();

	return true;
}

void GameBoard::createPuzzle()
{
	for (int i = 0; i < 30; i++)
	{
		PuzzlePiece *pPuzzlePiece = PuzzlePiece::create("puzzle" + std::to_string(i) + ".png");
		//this->addChild(pPuzzlePiece);
		addPuzzlePiece(pPuzzlePiece, &maskPuzzlePieces);		
	}
}

void GameBoard::addPuzzlePiece(PuzzlePiece* pPuzzlePiece, Vector<PuzzlePiece*> *vector)
{
	vector->pushBack(pPuzzlePiece);
}

PuzzlePiece* GameBoard::getPuzzlePiece(int index, Vector<PuzzlePiece*> vector)
{
	return vector.at(index);
}


void GameBoard::logic()
{
	auto size = Director::getInstance()->getWinSize();
	Sprite *puzzleImage = Sprite::create("maldive3.png");
	puzzleImage->setAnchorPoint(Point(0, 1));
	puzzleImage->setBlendFunc({ GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA });
	vector<Size> sizes;
	int distanceBeetweenPuzzleX = maskPuzzlePieces.at(0)->getContentSize().width * 0.5;
	for (int i = 0; i < 5; i++)
	{		
		Sprite *mask = maskPuzzlePieces.at(i);
		Size cs = mask->getContentSize();
		sizes.push_back(cs);
		mask->setPosition(Point(cs.width / 2, cs.height / 2));
		RenderTexture *rt = RenderTexture::create(cs.width, cs.height);
		if (i == 0)
		{
			auto check2 = i * -cs.width;
			puzzleImage->setPosition(Point(i * -cs.width, cs.height));
		}
		else
		{	
			auto _x = (sizes.at(i - 1).width * 32) / 100; // 32%
			puzzleImage->setPosition(Point(_x - sizes.at(i - 1).width, cs.height));
		}
		rt->beginWithClear(0, 0, 0, 0);
		mask->visit();
		puzzleImage->visit();
		Director::getInstance()->getRenderer()->render();
		rt->end();
		PuzzlePiece *rtSprite = PuzzlePiece::createWithTexture(rt->getSprite()->getTexture());
		addPuzzlePiece(rtSprite, &puzzlePieces);
		addChild(rtSprite);	
		rtSprite->setFlippedY(true);
		auto check = (i + 0.5) * cs.width;
		rtSprite->setPosition(Point(distanceBeetweenPuzzleX, size.height - cs.height / 2));
		distanceBeetweenPuzzleX = distanceBeetweenPuzzleX + 200;

		/*if (i == 0)
		{
			//rtSprite->setPosition(Point((i + 0.5) * cs.width, size.height - cs.height / 2));
		}
		else
		{
			if (i == 1)
			{
				rtSprite->setPosition(Point(55 + 122, size.height - cs.height / 2));
			}
		}*/
	}
}