#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics.hpp>
#include "Tetris.h"
#include "EventBuffer.h"

#endif

static const int FPS = 42;

class Game {
public:
	Game(sf::RenderWindow *window);
	void Init();
	void inputKey(sf::Event &evnet);
	void processInput();
	void setPause(bool flag);
	void setDelay(double delay);
	void updateFPS();
	void gameLoop();
	void update();
	void render();

private:
	const double MS_PER_UPDATE = 1. / FPS;
	sf::RenderWindow *window;
	Tetris tetris;
	sf::Texture block;
	sf::Sprite sprite;
	sf::Clock clock;
	double timer, lag, delay , fpsElapsed;
	int frameCount;
	bool isPaused;
};