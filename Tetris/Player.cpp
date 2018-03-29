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
	delay = 0.3;
	Tetris::Init();
}

void Player::setDelay(double _delay)
{
	delay = _delay;
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
			timer -= delay;
			delay = .3;
		}
	}
	else {
  		gameOver(timer / 0.2);
		if (timer > 5)Init();
	}
}

void Player::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);
	drawBackground(window);
	drawAllBlock(window);
	if (!isOver()) {
		drawNowBlock(window);
		drawPrediction(window);
	}
	window.display();
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
