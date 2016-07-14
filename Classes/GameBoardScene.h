#ifndef __GAMEBOARD_SCENE_H__
#define __GAMEBOARD_SCENE_H__

#include "cocos2d.h"
#include "PuzzlePiece.h"
#include <vector>

class GameBoard : public cocos2d::Layer
{
public:
	
	static cocos2d::Scene* createScene();	
	virtual bool init();
	void createPuzzle();
	void addPuzzlePiece(PuzzlePiece* pPuzzlePiece, Vector<PuzzlePiece*> *vector);
	PuzzlePiece* getPuzzlePiece(int index, Vector<PuzzlePiece*> vector);
	void logic();

	

private:
	cocos2d::Vector<PuzzlePiece*> maskPuzzlePieces;
	cocos2d::Vector<PuzzlePiece*> puzzlePieces;
	
	
	CREATE_FUNC(GameBoard);
};

#endif 