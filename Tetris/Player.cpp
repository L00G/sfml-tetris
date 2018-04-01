#include "Player.h"


Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	timer = 0;
	delay = 0.3 / speedState;
	Tetris::Init();
}

void Player::setDelay(double _delay)
{
	delay = _delay / speedState;
}

void Player::update(double time)
{
	timer += time;

	lineCheck();
	if (!isOver()) {
		newBlock();
		predict();

		while (timer > delay) {
			move(0, 1);
			timer -= delay ;
			delay = .3 / speedState;
		}
	}
	else {
  		gameOver(timer / 0.1);
		if (timer > 2)Init();
	}
}

void Player::render(sf::RenderWindow & window)
{
	drawBackground(window);
	drawAllBlock(window);
	if (!isOver()) {
		drawNowBlock(window);
		drawPrediction(window);
	}
}

void Player::drawPrediction(sf::RenderWindow & window)
{
	sprite.setColor(sf::Color(255, 255, 255, 80));
	for (int i = 0; i < 4; i++) {
		sprite.setPosition(sf::Vector2f(predictionPiece.getBlock(i).x * 20, 50 + predictionPiece.getBlock(i).y * 20));
		window.draw(sprite);
	}
	sprite.setColor(sf::Color(255, 255, 255, 255));
}

void Player::predict() {
	predictionPiece = piece;
	while (check()) {
		piece.move(0, 1);
	}
	piece.cancel();
	Piece::swap(piece, predictionPiece);
}
