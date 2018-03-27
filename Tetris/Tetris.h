#pragma once

#include<SFML/Graphics.hpp>
using namespace sf;

#define BOARD_WEIGHT 10
#define BOARD_HEIGHT 25

struct Point { int x, y; };
static int figures[8][4] = { { 0,0,0,0 } ,{ 1,3,5,7 },{ 2,4,5,7 },{ 3,5,4,6 },{ 3,5,4,7 },{ 2,3,5,7 },{ 3,5,7,6 },{ 2,3,4,5 } };

class Tetris {
public:
	Tetris();
	void Init();
	void NewBlock();
	bool check(Point pos[]);
	bool isOver();
	bool needNewBlock();
	void lineCheck();
	void Move(int dx);
	void HorMove(int dy);
	void Predict();
	void Drop();
	void Rotate();
	void DrawBackground(RenderWindow &window);
	void DrawBlock(RenderWindow &window);
	void Render(RenderWindow &window);
	void GameOverRender(RenderWindow &window);

private:
	Texture block;
	Sprite sprite;
	Point pos[4], tempPos[4], predictionPos[4], nextFigures[2][4];
	int board[BOARD_HEIGHT][BOARD_WEIGHT], figureNum[3];
	bool newBlockFlag;
};