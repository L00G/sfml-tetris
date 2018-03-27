#include "Game.h"

	Game::Game(RenderWindow *_window) {
		window = _window;
		Init();
	}
	void Game::Init() {
		tetris.Init();
		timer = 0; delay = .3;
		lag = 0;
		isPaused = false;
	}
	void Game::inputKey(Event &event)
	{
		EventBuffer::PushKey(event);
	}
	void Game::processInput()
	{
		if (!EventBuffer::isEmpty()) {
			Keyboard::Key key = EventBuffer::popKey();
			if (!isPaused) {
				switch (key) {
				case Keyboard::Right:tetris.Move(1); break;
				case Keyboard::Left:tetris.Move(-1); break;
				case Keyboard::Up:tetris.Rotate(); break;
				case Keyboard::Down:setDelay(.1); break;
				case Keyboard::Space:tetris.Drop(); break;
				default:break;
				}
			}
			if (key == Keyboard::P) {
				setPause(!isPaused);
			}
		}
	}
	void Game::setPause(bool flag) {
		isPaused = flag;
	}
	void Game::setDelay(double delay) {
		this->delay = delay;
	}
	void Game::UpdateFPS()
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
	void Game::GameLoop() {
		double time = clock.restart().asSeconds();
		processInput();
		timer += time;
		lag += time;
		while (lag >= MS_PER_UPDATE) {
			if (!isPaused) {
				Update();
			}
			lag -= MS_PER_UPDATE;
		}
		fpsElapsed += time;
		UpdateFPS();
		Render();
		double frameTime = clock.getElapsedTime().asSeconds();
		if(MS_PER_UPDATE > frameTime)
			sleep(seconds(MS_PER_UPDATE - frameTime));
	}
	void Game::Update() {	
		tetris.lineCheck();
		if (!tetris.isOver()) {
			if (tetris.needNewBlock())
				tetris.NewBlock();
			tetris.Predict();

			if (timer > delay) {
				tetris.HorMove(1);
				delay = .3;
				timer = 0;
			}
		}
	}
	void Game::Render()
	{
		if (tetris.isOver()) {
			tetris.GameOverRender(*window);
			Init();
		}
		else tetris.Render(*window);
	}
	