#ifndef _TETRIS_H_
#define _TETRIS_H_

#include<SFML/Graphics.hpp>
#include"Piece.h"

#endif

static const int BOARD_WEIGHT = 10;
static const int BOARD_HEIGHT = 25;

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
	void drawBackground(sf::RenderWindow &window);
	void drawBlock(sf::RenderWindow &window);
	void render(sf::RenderWindow &window);
	void gameOverRender(sf::RenderWindow &window);

private:
	sf::Texture block;
	sf::Sprite sprite;
	Piece piece, predictionPiece, nextPiece[2];
	int board[BOARD_HEIGHT][BOARD_WEIGHT];
	bool newBlockFlag;
};