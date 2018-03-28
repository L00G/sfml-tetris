#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"

#define BOARD_WEIGHT 10
#define BOARD_HEIGHT 25

int main() {
	sf::RenderWindow window(sf::VideoMode(400, 800),"Tetris");

	Game game = Game(&window);
	
	while (window.isOpen()) {		
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}		
			else if (event.type == sf::Event::KeyPressed) {
				game.inputKey(event);				
			}
		}
		game.gameLoop();
	}
	return 0;
}