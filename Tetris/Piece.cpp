#include "Piece.h"

Piece::Piece()
{
}


Piece::~Piece()
{
}

void Piece::newBlock()
{
	pieceNumber = SuffleBag::next();
	for (int i = 0; i < 4; i++) {
		block[i].x = pieces[pieceNumber][i] % 2;
		block[i].y = pieces[pieceNumber][i] / 2;
		preBlock[i] = block[i];
	}
}

Point Piece::getBlock(int index)
{
	return block[index];
}

int Piece::getNumber()
{
	return pieceNumber;
}

void Piece::move(int dx, int dy)
{
	for (int i = 0; i < 4; i++) {
		preBlock[i] = block[i];
		block[i].x += dx;
		block[i].y += dy;
	}
}

void Piece::rotate()
{
	for (int i = 0; i < 4; i++) preBlock[i] = block[i];
	Point piv = block[1];
	for (int i = 0; i < 4; i++) {
		int x = block[i].y - piv.y;
		int y = block[i].x - piv.x;
		block[i].x = piv.x - x;
		block[i].y = piv.y + y;
	}
}

void Piece::cancel()
{
	for (int i = 0; i < 4; i++)block[i] = preBlock[i];
}

void Piece::swap(Piece & a, Piece & b)
{
	Piece temp = a;
	a = b;
	b = temp;
}
