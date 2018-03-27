#include<SFML/Graphics.hpp>
#include "Game.h"
#include "EventBuffer.h"
using namespace sf;

#define BOARD_WEIGHT 10
#define BOARD_HEIGHT 25

int main() {
	RenderWindow window(VideoMode(400, 800),"Tetris");

	Game game = Game(&window);
	
	while (window.isOpen()) {		
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}		
			else if (event.type == Event::KeyPressed) {
				game.inputKey(event);				
			}
		}
		game.GameLoop();
	}
	return 0;
}