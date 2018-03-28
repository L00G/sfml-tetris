#include "SuffleBag.h"

void SuffleBag::fill()
{
	srand(time_t(NULL));
	int i = 1;
	for (std::pair<std::string, int> piece : piecesPercent) {
		add(i++, piece.second);
	}
}

void SuffleBag::add(int nubmer, int count)
{
	for (int i = 0; i < count; i++)
		pool[++pos] = nubmer;
}

int SuffleBag::next()
{
	if (pos == -1)fill();
	int random = rand() % pos;
	if(pool[random]==preNumber)random = rand() % pos;
	int temp = pool[pos];
	pool[pos] = pool[random];
	pool[random] = temp;
	return pool[pos--];
}
