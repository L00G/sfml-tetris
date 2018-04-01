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
	void drawPrediction(sf::RenderWindow &window);
	virtual void render(sf::RenderWindow & window) override;	
private:
	Piece predictionPiece;
};

