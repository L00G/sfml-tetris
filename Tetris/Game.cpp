#include "Game.h"

	Game::Game(sf::RenderWindow *_window) {
		window = _window;
		Init();
	}
	void Game::Init(){
		clock.restart();
		pplayer->Init();
		lag = 0;
		isPaused = false;
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
				case sf::Keyboard::Right:pplayer->move(1,0); break;
				case sf::Keyboard::Left:pplayer->move(-1,0); break;
				case sf::Keyboard::Up:pplayer->rotate(); break;
				case sf::Keyboard::Down:((Player*)pplayer)->setDelay(.1); break;
				case sf::Keyboard::Space:pplayer->drop(); break;
				default:break;
				}
			}
			if (key == sf::Keyboard::P) {
				setPause(!isPaused);
			}
		}
	}
	void Game::setPause(bool flag) {
		isPaused = flag;
	}
	void Game::updateFPS()
	{
		frameCount++;
		if (fpsElapsed >= 1.0f)     
		{
			int fps = (double)frameCount / fpsElapsed;
			char str[30];
			sprintf_s(str, "FPS : %d", fps);
			window->setTitle(str);
			frameCount = 0;
			fpsElapsed = 0;
		}
	}
	void Game::gameLoop() {
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
		render();
		double frameTime = clock.getElapsedTime().asSeconds();
		if(MS_PER_UPDATE > frameTime)
			sf::sleep(sf::seconds(MS_PER_UPDATE - frameTime));
	}
	void Game::update(double time) {
		pplayer->update(time);
	}
	void Game::render()
	{
		pplayer->render(*window);
	}