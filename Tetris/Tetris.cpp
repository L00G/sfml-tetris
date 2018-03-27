#include "Tetris.h"

Tetris::Tetris() {
	srand(time(NULL));
	block.loadFromFile("block.png");
	sprite = Sprite(block);
	Init();
}
void Tetris::Init()
{
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WEIGHT; j++) {
			board[i][j] = 0;
		}
	}
	for (int i = 0; i < 3; i++) figureNum[i] = rand() % 7 + 1;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			nextFigures[i][j].x = figures[figureNum[i + 1]][j] % 2;
			nextFigures[i][j].y = figures[figureNum[i + 1]][j] / 2;
		}
	}
	NewBlock();
}
void Tetris::NewBlock() {
	figureNum[0] = figureNum[1]; figureNum[1] = figureNum[2]; figureNum[2] = rand() % 7 + 1;
	for (int i = 0; i < 4; i++) { pos[i] = nextFigures[0][i]; nextFigures[0][i] = nextFigures[1][i]; }
	for (int i = 0; i < 4; i++) {
		nextFigures[1][i].x = figures[figureNum[2]][i] % 2;
		nextFigures[1][i].y = figures[figureNum[2]][i] / 2;
	}
	newBlockFlag = false;
}
bool Tetris::check(Point pos[]) {
	for (int i = 0; i < 4; i++) {
		if (pos[i].x < 0 || pos[i].x >= BOARD_WEIGHT || pos[i].y >= BOARD_HEIGHT)return false;
		if (board[pos[i].y][pos[i].x]) return false;
	}
	return true;
}
bool Tetris::isOver() {
	for (int i = 0; i < BOARD_WEIGHT; i++) {
		if (board[5][i] != 0) {
			return true;
		}
	}
	return false;
}
bool Tetris::needNewBlock()
{
	return newBlockFlag;
}
void Tetris::lineCheck() {
	int y = BOARD_HEIGHT - 1;
	for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
		int cnt = 0;
		for (int x = 0; x < BOARD_WEIGHT; x++) {
			if (board[i][x])cnt++;
			board[y][x] = board[i][x];
		}
		if (cnt != BOARD_WEIGHT) y--;
	}
}
void Tetris::Move(int dx) {
	for (int i = 0; i < 4; i++) { tempPos[i] = pos[i]; pos[i].x += dx; }
	if (!check(pos))for (int i = 0; i < 4; i++)pos[i] = tempPos[i];
}
void Tetris::HorMove(int dy) {
	for (int i = 0; i < 4; i++) { tempPos[i] = pos[i]; pos[i].y += dy; }
	if (!check(pos)) {
		for (int i = 0; i < 4; i++)	board[tempPos[i].y][tempPos[i].x] = figureNum[0];
		for (int i = 0; i < 4; i++) pos[i] = tempPos[i];
		newBlockFlag = true;
	}
}
void Tetris::Predict() {
	for (int i = 0; i < 4; i++) { tempPos[i] = pos[i]; }
	while (check(pos)) {
		for (int i = 0; i < 4; i++) { predictionPos[i] = pos[i]; pos[i].y += 1; }
	}
	for (int i = 0; i < 4; i++)pos[i] = tempPos[i];
}
void Tetris::Drop() {
	while (check(pos)) {
		for (int i = 0; i < 4; i++) { tempPos[i] = pos[i]; pos[i].y += 1; }
	}
	for (int i = 0; i < 4; i++)	board[tempPos[i].y][tempPos[i].x] = figureNum[0];
	for (int i = 0; i < 4; i++) pos[i] = tempPos[i];
	newBlockFlag = true;
}
void Tetris::Rotate() {
	for (int i = 0; i < 4; i++) tempPos[i] = pos[i];
	Point piv = pos[1];
	for (int i = 0; i < 4; i++) {
		int x = pos[i].y - piv.y;
		int y = pos[i].x - piv.x;
		pos[i].x = piv.x - x;
		pos[i].y = piv.y + y;
	}
	if (!check(pos))for (int i = 0; i < 4; i++)pos[i] = tempPos[i];
}
void Tetris::DrawBackground(RenderWindow &window) {
	CircleShape dot(2.f);
	dot.setFillColor(Color(52, 52, 52, 150));
	for (int i = 0; i < 10; i++) {
		dot.setPosition(Vector2f(i * 20 + 8, 50 + 5 * 20));
		window.draw(dot);
	}
	for (int j = 0; j < 2; j++) {
		sprite.setTextureRect(IntRect((figureNum[j + 1] - 1) * 20, 0, 20, 20));
		for (int i = 0; i < 4; i++) {
			sprite.setPosition(Vector2f(nextFigures[j][i].x * 20 + 200 + j * 50, 50 + nextFigures[j][i].y * 20 + 200));
			window.draw(sprite);
		}
	}
}
void Tetris::DrawBlock(RenderWindow &window) {
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WEIGHT; x++) {
			if (board[y][x]) {
				sprite.setTextureRect(IntRect((board[y][x] - 1) * 20, 0, 20, 20));
				sprite.setPosition(Vector2f(x * 20, 50 + y * 20));
				window.draw(sprite);
			}
		}
	}
	sprite.setTextureRect(IntRect((figureNum[0] - 1) * 20, 0, 20, 20));
	for (int i = 0; i < 4; i++) {
		sprite.setPosition(Vector2f(pos[i].x * 20, 50 + pos[i].y * 20));
		window.draw(sprite);
	}
	sprite.setColor(Color(255, 255, 255, 80));
	sprite.setTextureRect(IntRect((figureNum[0] - 1) * 20, 0, 20, 20));
	for (int i = 0; i < 4; i++) {
		sprite.setPosition(Vector2f(predictionPos[i].x * 20, 50 + predictionPos[i].y * 20));
		window.draw(sprite);
	}
	sprite.setColor(Color(255, 255, 255, 255));
}
void Tetris::Render(RenderWindow &window) {
	window.clear(Color::White);
	DrawBackground(window);
	DrawBlock(window);
	window.display();
}
void Tetris::GameOverRender(RenderWindow &window) {
	Clock clock;
	float time =0;
	for (int i = 0; i < BOARD_HEIGHT;) {
		time += clock.restart().asSeconds();
     	if (time < 0.1)continue;
		window.clear(Color::White);
		DrawBackground(window);
		DrawBlock(window);
		sprite.setTextureRect(IntRect(0, 0, 20, 20));
		sprite.setColor(Color(100, 100, 100, 255));
		for (int y = 0; y < i; y++) {
			for (int x = 0; x < BOARD_WEIGHT; x++) {
				if (board[y][x]) {
					sprite.setPosition(Vector2f(x * 20, 50 + y * 20));
					window.draw(sprite);
				}
			}
		}
		sprite.setColor(Color(255, 255, 255, 255));
		window.display();
		time -= 0.1;
		i++;
	}
}
