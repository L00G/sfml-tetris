#include "Tetris.h"

Tetris::Tetris() {
	srand(time(NULL));
	block.loadFromFile("block.png");
	sprite = Sprite(block);
}
void Tetris::Init()
{
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WEIGHT; j++) {
			board[i][j] = 0;
		}
	}
	piece.newBlock();
	for (int i = 0; i < 2; i++)nextPiece[i].newBlock();
	newBlockFlag = false;
}
void Tetris::newBlock() {
	if (newBlockFlag) {
		piece = nextPiece[0]; nextPiece[0] = nextPiece[1]; nextPiece[1].newBlock();
		newBlockFlag = false;
	}
}
bool Tetris::check() {
	for (int i = 0; i < 4; i++) {
		if (piece.getBlock(i).x < 0 || piece.getBlock(i).x >= BOARD_WEIGHT || piece.getBlock(i).y >= BOARD_HEIGHT)return false;
		if (board[piece.getBlock(i).y][piece.getBlock(i).x]) return false;
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
void Tetris::move(int dx, int dy) {
	piece.move(dx, dy);
	if (!check()) {
		piece.cancel();
		if (dy) {
			for (int i = 0; i < 4; i++)	board[piece.getBlock(i).y][piece.getBlock(i).x] = piece.getNumber();
			newBlockFlag = true;
		}
	}
}
void Tetris::predict() {
	predictionPiece = piece;
	while (check()) {
		piece.move(0, 1);
	}
	piece.cancel();
	Piece::swap(piece, predictionPiece);
}
void Tetris::drop() {
	while (!newBlockFlag) {
		HorMove(1);
	}
}
void Tetris::Rotate() {
	piece.rotate();
	if (!check())piece.cancel();
}
void Tetris::drawBackground(RenderWindow &window) {
	CircleShape dot(2.f);
	dot.setFillColor(Color(52, 52, 52, 150));
	for (int i = 0; i < 10; i++) {
		dot.setPosition(Vector2f(i * 20 + 8, 50 + 5 * 20));
		window.draw(dot);
	}
	for (int j = 0; j < 2; j++) {
		sprite.setTextureRect(IntRect((nextPiece[j].getNumber() - 1) * 20, 0, 20, 20));
		for (int i = 0; i < 4; i++) {
			sprite.setPosition(Vector2f(nextPiece[j].getBlock(i).x * 20 + 200 + j * 50, 50 + nextPiece[j].getBlock(i).y * 20 + 200));
			window.draw(sprite);
		}
	}
}
void Tetris::drawBlock(RenderWindow &window) {
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WEIGHT; x++) {
			if (board[y][x]) {
				sprite.setTextureRect(IntRect((board[y][x] - 1) * 20, 0, 20, 20));
				sprite.setPosition(Vector2f(x * 20, 50 + y * 20));
				window.draw(sprite);
			}
		}
	}
	sprite.setTextureRect(IntRect((piece.getNumber() - 1) * 20, 0, 20, 20));
	for (int i = 0; i < 4; i++) {
		sprite.setPosition(Vector2f(piece.getBlock(i).x * 20, 50 + piece.getBlock(i).y * 20));
		window.draw(sprite);
	}

	sprite.setColor(Color(255, 255, 255, 80));
	for (int i = 0; i < 4; i++) {
		sprite.setPosition(Vector2f(predictionPiece.getBlock(i).x * 20, 50 + predictionPiece.getBlock(i).y * 20));
		window.draw(sprite);
	}
	sprite.setColor(Color(255, 255, 255, 255));
}
void Tetris::render(RenderWindow &window) {
	window.clear(Color::White);
	drawBackground(window);
	drawBlock(window);
	window.display();
}
void Tetris::gameOverRender(RenderWindow &window) {
	Clock clock;
	float time = 0;
	for (int i = 0; i < BOARD_HEIGHT;) {
		time += clock.restart().asSeconds();
		if (time < 0.1)continue;
		window.clear(Color::White);
		drawBackground(window);
		drawBlock(window);
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
