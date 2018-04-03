#include "Game.h"

	Game::Game() {

	}
	void Game::Init(){
		clock.restart();
		lag = 0;
		play = true;
		isPaused = false;
		tetris->Init();
	}
	void Game::startAI()
	{
		tetris = new AI();
		Init();
	}
	void Game::startGenetic(int _numberRepetitions, int _generationNumber)
	{
		tetris = new AI(_numberRepetitions, _generationNumber);
		Init();
	}
	void Game::startPlayer()
	{		
		tetris = new Player();
		Init();
	}
	void Game::inputKey(sf::Event &event)
	{
		EventBuffer::PushKey(event);
	}
	void Game::processInput()
	{
		if (!EventBuffer::isEmpty()) {
			sf::Keyboard::Key key = EventBuffer::popKey();
			if (!isPaused) {
				switch (key) {
				case sf::Keyboard::Right:tetris->move(1,0); break;
				case sf::Keyboard::Left:tetris->move(-1,0); break;
				case sf::Keyboard::Up:tetris->rotate(); break;
				case sf::Keyboard::Down:((Player*)tetris)->setDelay(.1); break;
				case sf::Keyboard::Space:tetris->drop(); break;
				case sf::Keyboard::Add:tetris->speedUp(); break;
				case sf::Keyboard::Subtract:tetris->speedDown(); break;
				case sf::Keyboard::Escape:play = false; break;
				default:break;
				}
			}
			if (key == sf::Keyboard::P) {
				setPause(!isPaused);
			}
		}
	}
	bool Game::isPlay() {
		return play;
	}
	void Game::setPause(bool flag) {
		isPaused = flag;
	}
	void Game::updateFPS()
	{
		frameCount++;
		if (fpsElapsed >= 1.0f)     
		{
			fps = (double)frameCount / fpsElapsed;
			frameCount = 0;
			fpsElapsed = 0;
		}
	}
	void Game::gameLoop(sf::RenderWindow &window)
	{
		double time = clock.restart().asSeconds();
		processInput();
		lag += time;
		while (lag >= MS_PER_UPDATE) {
			if (!isPaused) {
				update(MS_PER_UPDATE);
			}
			lag -= MS_PER_UPDATE;
		}
		fpsElapsed += time;
		updateFPS();
		render(window);
		double frameTime = clock.getElapsedTime().asSeconds();
		if (MS_PER_UPDATE > frameTime)
			sf::sleep(sf::seconds(MS_PER_UPDATE - frameTime));
	}
	void Game::update(double time) {
		tetris->update(time);
	}
	void Game::render(sf::RenderWindow &window)
	{	
		window.clear();	
		tetris->render(window);
		window.display();
	}