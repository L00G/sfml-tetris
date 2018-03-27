#pragma once

#include<SFML/Graphics.hpp>
#include"Tetris.h"
#include "EventBuffer.h"
using namespace sf;

#define FPS 144

class Game {
public:
	Game(RenderWindow *window);
	void Init();
	void inputKey(Event &evnet);
	void processInput();
	void setPause(bool flag);
	void setDelay(double delay);
	void updateFPS();
	void gameLoop();
	void update();
	void render();

private:
	const double MS_PER_UPDATE = 1. / FPS;
	RenderWindow *window;
	Tetris tetris;
	Texture block;
	Sprite sprite;
	Clock clock;
	double timer, lag, delay , fpsElapsed;
	int frameCount;
	bool isPaused;
};