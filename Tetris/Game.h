#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "AI.h"
#include "EventBuffer.h"

static const int FPS = 144;

class Game {
public:
	Game();
	void Init();
	void startAI();
	void startGenetic(int _numberRepetitions, int _generationNumber);
	void startPlayer();
	void inputKey(sf::Event &evnet);
	void processInput();
	bool isPlay();
	void setPause(bool flag);
	void updateFPS();
	void gameLoop(sf::RenderWindow &window);
	void update(double time);
	void render(sf::RenderWindow &window);

private:
	const double MS_PER_UPDATE = 1. / FPS;
	Tetris *tetris;
	sf::Clock clock;
	double lag, fpsElapsed;
	int fps,frameCount;
	bool isPaused,play;
};

#endif
