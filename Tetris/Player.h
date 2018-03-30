#pragma once

#include "Tetris.h"

class Player : public Tetris
{
public:
	Player();
	~Player();
	void Init();
	void predict();
	void setDelay(double _delay);
	virtual void update(double time) override;
	virtual void render(sf::RenderWindow & window) override;
	void drawPrediction(sf::RenderWindow &window);
private:
	Piece predictionPiece;
	double timer;
};

