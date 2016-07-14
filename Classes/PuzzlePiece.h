#ifndef _PUZZLE_PIECE_H_
#define _PUZZLE_PIECE_H_

#include "cocos2d.h"

using namespace std;

USING_NS_CC;

class PuzzlePiece : public cocos2d::Sprite
{
public:
	PuzzlePiece();
	~PuzzlePiece();
	static PuzzlePiece* create(const std::string& fileName);
	static PuzzlePiece* createWithTexture(Texture2D *texture);
	void onEnter();
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void setPuzzleFileName(const std::string& fileName);
	void setConvex_X(int x_convex);
	void setConvex_Y(int y_convex);
	int getConvex_X();
	int getConvex_Y();
	void setNumberConvex(int number_convex);
	int getNumberConvex();
	void setPercent(int percent);

private:
	int x_convex;
	int y_convex;
	int number_convex;
	string fileName;
	int percent;
};

#endif //