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
	Sprite *puzzleImage = Sprite::create("maldive3.1.png");
	puzzleImage->setAnchorPoint(Point(0, 1));
	puzzleImage->setBlendFunc({ GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA });
	vector<Size> sizes;
	int distanceBeetweenPuzzleX = maskPuzzlePieces.at(0)->getContentSize().width * 0.5;
	for (int i = 0; i < 13; i++)
	{		
		Sprite *mask = maskPuzzlePieces.at(i);
		Size cs = mask->getContentSize();
		sizes.push_back(cs);
		mask->setPosition(Point(cs.width / 2, cs.height / 2));
		RenderTexture *rt = RenderTexture::create(cs.width, cs.height);
		if (i == 0)
		{			
			puzzleImage->setPosition(Point(i * -cs.width, cs.height));			
		}
		else if (i == 1)
		{
			auto _x = (sizes.at(i - 1).width * 32) / 100; // 32%
			getPuzzlePiece(0, this->maskPuzzlePieces)->setConvex_X(_x);
			puzzleImage->setPosition(Point(_x - sizes.at(i - 1).width, cs.height));
		}
		else if (i == 2)
		{
			auto _x = (sizes.at(2).width * 34.2) / 100;// 34 norm
			getPuzzlePiece(2, this->maskPuzzlePieces)->setConvex_X(_x);
			puzzleImage->setPosition(Point(_x - (sizes.at(0).width + sizes.at(1).width -
				getPuzzlePiece(0, this->maskPuzzlePieces)->getConvex_X()), cs.height));
		}
		else if (i == 3)
		{
			puzzleImage->setPosition(Point(getPuzzlePiece(2, this->maskPuzzlePieces)->getConvex_X() -
				(sizes.at(0).width + sizes.at(1).width + sizes.at(2).width -
				(getPuzzlePiece(0, this->maskPuzzlePieces)->getConvex_X() + getPuzzlePiece(2, this->maskPuzzlePieces)->getConvex_X())), cs.height));
		}
		else if (i == 4)
		{
			puzzleImage->setPosition(Point(getPuzzlePiece(2, this->maskPuzzlePieces)->getConvex_X() -
				(sizes.at(0).width + sizes.at(1).width + sizes.at(2).width + sizes.at(3).width -
				(getPuzzlePiece(0, this->maskPuzzlePieces)->getConvex_X() + getPuzzlePiece(2, this->maskPuzzlePieces)->getConvex_X() * 2)), cs.height));
		}
		else if (i == 5)
		{			
			auto _x = (sizes.at(2).width * 30.5) / 100;
			puzzleImage->setPosition(Point(_x -
				(sizes.at(0).width + sizes.at(1).width + sizes.at(2).width + sizes.at(3).width + sizes.at(4).width -
				(getPuzzlePiece(0, this->maskPuzzlePieces)->getConvex_X() + getPuzzlePiece(2, this->maskPuzzlePieces)->getConvex_X() * 3)), cs.height));
		}
		else if (i == 6)
		{			
			auto _y = (sizes.at(0).height* 26) / 100;			
			puzzleImage->setPosition(Point(0 * -cs.width, cs.height + sizes.at(0).height - _y));
		}
		else if (i == 7)
		{
			auto _x = (sizes.at(6).width * 25) / 100;
			auto _y = (sizes.at(1).height * 32) / 100;
			puzzleImage->setPosition(Point(_x - sizes.at(i - 1).width, cs.height + sizes.at(1).height - _y));
		}
		else if (i == 8)
		{
			auto _y = (sizes.at(0).height * 26) / 100;
			auto _x = (sizes.at(6).width * 28) / 100;
			puzzleImage->setPosition(Point(_x - (sizes.at(i - 1).width)*2, cs.height + sizes.at(0).height - _y));
		}
		else if (i == 9)
		{
			auto _x = (sizes.at(6).width * 22) / 100;
			auto _y = (sizes.at(1).height * 32) / 100;
			puzzleImage->setPosition(Point(_x - sizes.at(i - 1).width*2, cs.height + sizes.at(1).height - _y));
		}
		else if (i == 10)
		{
			auto _y = (sizes.at(0).height * 26) / 100;
			auto _x = (sizes.at(6).width * 32) / 100;
			puzzleImage->setPosition(Point(_x - (sizes.at(i - 1).width) * 4, cs.height + sizes.at(0).height - _y));
		}
		else if (i = 11)
		{
			auto _x = (sizes.at(6).width * 22) / 100;
			auto _y = (sizes.at(1).height * 32) / 100;
			puzzleImage->setPosition(Point(_x - sizes.at(i - 1).width * 5, cs.height + sizes.at(1).height - _y));
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
		if (i > 4)
		{
			rtSprite->setPosition(Vec2(300, 300));
		}			
		else
		{
			rtSprite->setPosition(Point(distanceBeetweenPuzzleX, size.height - cs.height / 2));
		}		
		distanceBeetweenPuzzleX = distanceBeetweenPuzzleX + 100;
	}
}