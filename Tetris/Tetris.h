#pragma once

#include<SFML/Graphics.hpp>
#include"Piece.h"
using namespace sf;

#define BOARD_WEIGHT 10
#define BOARD_HEIGHT 25

class Tetris {
public:
	Tetris();
	void Init();
	void newBlock();
	bool check();
	bool isOver();
	void lineCheck();
	void move(int dx,int dy);
	void predict();
	void drop();
	void Rotate();
	void drawBackground(RenderWindow &window);
	void drawBlock(RenderWindow &window);
	void render(RenderWindow &window);
	void gameOverRender(RenderWindow &window);

private:
	Texture block;
	Sprite sprite;
	Piece piece, predictionPiece, nextPiece[2];
	int board[BOARD_HEIGHT][BOARD_WEIGHT];
	bool newBlockFlag;
};