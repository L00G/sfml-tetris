#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "EventBuffer.h"

#endif

static const int FPS = 144;

class Game {
public:
	Game(sf::RenderWindow *window);
	void Init();
	void inputKey(sf::Event &evnet);
	void processInput();
	void setPause(bool flag);
	void updateFPS();
	void gameLoop();
	void update(double time);
	void render();

private:
	const double MS_PER_UPDATE = 1. / FPS;
	sf::RenderWindow *window;
	Tetris *pplayer= new Player();;
	sf::Texture block;
	sf::Sprite sprite;
	sf::Clock clock;
	double lag, fpsElapsed;
	int frameCount;
	bool isPaused;
};