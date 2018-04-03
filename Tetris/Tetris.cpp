#include "Tetris.h"

Tetris::Tetris() {
	speedState = 1;
	srand(time(NULL));
	block.loadFromFile("block.png");
	backgroud.loadFromFile("background.png");
	backgroundSprite = sf::Sprite(backgroud);
	sprite = sf::Sprite(block);
	font.loadFromFile("AllAgesDEMO.ttf");
	SoundManager::Init();
}
void Tetris::Init()
{
	lineCount = 0;
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WEIGHT; j++) {
			board[i][j] = 0;
		}
	}
	piece.newBlock();
	for (int i = 0; i < 2; i++)nextPiece[i].newBlock();
	newBlockFlag = false;
}
void Tetris::speedUp()
{
	speedState++;
}
void Tetris::speedDown()
{
	speedState--;
	if (speedState < 1)speedState = 1;
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
	bool clear = false;
	int y = BOARD_HEIGHT - 1;
	for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
		int cnt = 0;
		for (int x = 0; x < BOARD_WEIGHT; x++) {
			if (board[i][x])cnt++;
			board[y][x] = board[i][x];
		}
		if (cnt != BOARD_WEIGHT) y--;
		else {
			lineCount++;
			clear = true;
		}
	}
	if(clear)SoundManager::PlaySound(SoundManager::SOUND::LINE_CLEAR);
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
	else {
		if(dx)SoundManager::PlaySound(SoundManager::SOUND::MOVE_LR);
	}
}
void Tetris::drop() {
	SoundManager::PlaySound(SoundManager::SOUND::HARD_DROP);
	while (!newBlockFlag) {
		move(0,1);
	}
}
void Tetris::rotate() {
	SoundManager::PlaySound(SoundManager::SOUND::ROTATE_LR);
	piece.rotate();
	if (!check())piece.cancel();
}
void Tetris::drawBackground(sf::RenderWindow &window) {	
	sf::Text text;
	text.setFillColor(sf::Color::Blue);
	text.setFont(font);
	text.setString(std::to_string(lineCount));
	text.setCharacterSize(20);
	text.setPosition(sf::Vector2f(100., 100.));
	window.draw(text);

	window.draw(backgroundSprite);

	sf::CircleShape dot(2.f);
	dot.setFillColor(sf::Color(52, 52, 52, 150));
	for (int i = 0; i < 10; i++) {
		dot.setPosition(sf::Vector2f(i * 20 + 8, 50 + 5 * 20));
		window.draw(dot);
	}
	for (int j = 0; j < 2; j++) {
		sprite.setTextureRect(sf::IntRect((nextPiece[j].getNumber()-1) * 20, 0, 20, 20));
		for (int i = 0; i < 4; i++) {
			sprite.setPosition(sf::Vector2f(nextPiece[j].getBlock(i).x * 20 + 200 + j * 50, 50 + nextPiece[j].getBlock(i).y * 20 + 200));
			window.draw(sprite);
		}
	}
}
void Tetris::drawAllBlock(sf::RenderWindow &window) {
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WEIGHT; x++) {
			if (board[y][x]) {
				sprite.setTextureRect(sf::IntRect((board[y][x] - 1) * 20, 0, 20, 20));
				sprite.setPosition(sf::Vector2f(100 + x * 20, 200 + y * 20));
				window.draw(sprite);
			}
		}
	}
}
void Tetris::drawNowBlock(sf::RenderWindow &window) {
	sprite.setTextureRect(sf::IntRect((piece.getNumber() - 1) * 20, 0, 20, 20));
	for (int i = 0; i < 4; i++) {
		sprite.setPosition(sf::Vector2f(100 + piece.getBlock(i).x * 20, 200 + piece.getBlock(i).y * 20));
		window.draw(sprite);
	}
}
void Tetris::gameOver(int height) {
	for (int x = 0; x < BOARD_WEIGHT; x++) {
		if (board[height][x]) {
			board[height][x] = 8;
		}
	}
}
