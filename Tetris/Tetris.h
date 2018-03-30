#ifndef _TETRIS_H_
#define _TETRIS_H_

#include<SFML/Graphics.hpp>
#include"Piece.h"

static const int BOARD_WEIGHT = 10;
static const int BOARD_HEIGHT = 25;

class Tetris {
public:
	Tetris();
	virtual void Init();
	void speedUp();
	void speedDown();
	void newBlock();
	bool check();
	bool isOver();
	void lineCheck();
	void move(int dx,int dy);
	void drop();
	void rotate();
	virtual void update(double time) = 0;
	virtual void render(sf::RenderWindow &window) = 0;
	void drawBackground(sf::RenderWindow &window);
	void drawAllBlock(sf::RenderWindow &window);
	void drawNowBlock(sf::RenderWindow & window);
	void gameOver(int height);

protected:
	sf::Texture block;
	sf::Sprite sprite;
	Piece piece, nextPiece[2];
	double delay;
	int board[BOARD_HEIGHT][BOARD_WEIGHT];
	int speedState = 1;
	bool newBlockFlag;
};

#endif