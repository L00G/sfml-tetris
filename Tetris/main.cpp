#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"

#define BOARD_WEIGHT 10
#define BOARD_HEIGHT 25

int menu(sf::RenderWindow &window) {
	bool choice = false;
	int choiceNumber = 0;

	sf::Font font;
	font.loadFromFile("AllAgesDEMO.ttf");

	sf::Text menuText("Menu", font, 50);
	menuText.setPosition(sf::Vector2f(140, 100));
	sf::Text playText("Play Game", font, 30);
	playText.setPosition(sf::Vector2f(130, 230));
	sf::Text GeneticText("Genetic Algorithm", font, 30);
	GeneticText.setPosition(sf::Vector2f(60, 360));
	sf::Text GeneticTestText("Genetic Result Test", font, 30);
	GeneticTestText.setPosition(sf::Vector2f(60, 490));
	sf::Text ExitText("Exit", font, 30);
	ExitText.setPosition(sf::Vector2f(170, 630));

	while (window.isOpen()&&!choice) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				choice = true;
				choiceNumber = -1;
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Up:choiceNumber--; if (choiceNumber < 0)choiceNumber = 1; break;
				case sf::Keyboard::Down:choiceNumber = (choiceNumber + 1) % 4; break;
				case sf::Keyboard::Return:choice = true;
				}
			}
		}
		window.clear(sf::Color::Black);
		window.draw(menuText);
		playText.setFillColor((choiceNumber == 0)?sf::Color::Color(100,180,240): sf::Color::White);
		GeneticText.setFillColor((choiceNumber == 1) ? sf::Color::Color(100, 180, 240) : sf::Color::White);	
		GeneticTestText.setFillColor((choiceNumber == 2) ? sf::Color::Color(100, 180, 240) : sf::Color::White);
		ExitText.setFillColor((choiceNumber == 3) ? sf::Color::Color(100, 180, 240) : sf::Color::White);
		window.draw(playText);
		window.draw(GeneticText);
		window.draw(GeneticTestText);
		window.draw(ExitText);
		window.display();
	}
	return choiceNumber;
}

std::pair<int,std::pair<int,int>> geneticMenu(sf::RenderWindow &window) {
	bool choice = false;
	int choiceNumber = 0;
	int config[2] = { 10,10 };

	sf::Font font;
	font.loadFromFile("AllAgesDEMO.ttf");

	sf::Text menuText("Select", font, 50);
	menuText.setPosition(sf::Vector2f(120, 100));
	sf::Text genText("Generation Count", font, 30);
	genText.setPosition(sf::Vector2f(20, 230));
	sf::Text repeatText("Repeat Num", font, 30);
	repeatText.setPosition(sf::Vector2f(80, 360));
	sf::Text StartText("Start", font, 30);
	StartText.setPosition(sf::Vector2f(160, 490));
	sf::Text BackText("Back", font, 30);
	BackText.setPosition(sf::Vector2f(170, 620));

	sf::Text count1("10", font, 30);
	count1.setPosition(sf::Vector2f(330, 230));
	sf::Text count2("10", font, 30);
	count2.setPosition(sf::Vector2f(330, 360));

	while (window.isOpen() && !choice) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				choice = true;
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Up:choiceNumber--; if (choiceNumber < 0)choiceNumber = 1; break;
				case sf::Keyboard::Down:choiceNumber = (choiceNumber + 1) % 4; break;
				case sf::Keyboard::Right:if (choiceNumber < 2)config[choiceNumber]++; break;
				case sf::Keyboard::Left:if (choiceNumber < 2 && config[choiceNumber]>10)config[choiceNumber]--; break;
				case sf::Keyboard::Return:if(choiceNumber>=2)choice = true;
				}
			}
		}
		window.clear(sf::Color::Black);
		window.draw(menuText);
		genText.setFillColor((choiceNumber == 0) ? sf::Color::Color(100, 180, 240) : sf::Color::White);
		repeatText.setFillColor((choiceNumber == 1) ? sf::Color::Color(100, 180, 240) : sf::Color::White);
		StartText.setFillColor((choiceNumber == 2) ? sf::Color::Color(100, 180, 240) : sf::Color::White);
		BackText.setFillColor((choiceNumber == 3) ? sf::Color::Color(100, 180, 240) : sf::Color::White);
		count1.setString(std::to_string(config[0]));
		count2.setString(std::to_string(config[1]));
		window.draw(genText);
		window.draw(count1);
		window.draw(repeatText);
		window.draw(count2);
		window.draw(StartText);
		window.draw(BackText);
		window.display();
	}
	return std::make_pair(choiceNumber,std::make_pair(config[0],config[1]));
}

int main() {
	sf::RenderWindow window(sf::VideoMode(400, 800), "Tetris");
	
	Game game;
	int choice = -1;
	while (window.isOpen()) {
		choice = menu(window);
		if (choice == 0)game.startPlayer();
		else if (choice == 1) {
			std::pair<int, std::pair<int, int>> data = geneticMenu(window);
			if (data.first == 2)game.startGenetic(data.second.first, data.second.second);
		}
		else if (choice == 2) {
			if (!_waccess_s(L"offset.txt", 0)) {
				game.startAI();
			}
			else {
				sf::RenderWindow dialog(sf::VideoMode(300, 100), "fail");
				sf::Font font;
				font.loadFromFile("arial.ttf");
				sf::Text text("You must run the genetuc algorithm at least once", font, 12);
				text.setFillColor(sf::Color::Black);
				text.setPosition(sf::Vector2f(20, 40));
				window.setActive(false);
				dialog.clear(sf::Color::White);
				dialog.draw(text);
				dialog.display();
				while (dialog.isOpen()) {
					sf::Event event;
					while (dialog.pollEvent(event)) {
						if (event.type == sf::Event::Closed) {
							dialog.close();
						}
					}
				}
				window.setActive(true);
			}
		}
		else break;
		while (window.isOpen() && game.isPlay()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
				else if (event.type == sf::Event::KeyPressed) {
					game.inputKey(event);
				}
			}
			game.gameLoop(window);
		}
	}
	window.close();
	return 0;
}