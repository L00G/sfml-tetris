#pragma once

#include<random>

struct Point { int x, y; };
static int pieces[8][4] = { { 0,0,0,0 } ,{ 1,3,5,7 },{ 2,4,5,7 },{ 3,5,4,6 },{ 3,5,4,7 },{ 2,3,5,7 },{ 3,5,7,6 },{ 2,3,4,5 } };

class Piece
{
public:
	Piece();
	~Piece();
	void newBlock();
	Point getBlock(int index);
	int getNumber();
	void move(int dx ,int dy);
	void rotate();
	void cancel();
	static void swap(Piece &a, Piece &b);
private:
	Point preBlock[4];
	Point block[4];
	int pieceNumber;
};
