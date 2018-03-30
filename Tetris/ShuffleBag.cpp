#include "ShuffleBag.h"

void ShuffleBag::fill()
{
	srand(time(NULL));
	int i = 1;
	for (std::pair<std::string, int> piece : piecesPercent) {
		add(i++, piece.second);
	}
}

void ShuffleBag::add(int nubmer, int count)
{
	for (int i = 0; i < count; i++)
		pool[++pos] = nubmer;
}

int ShuffleBag::next()
{
	if (pos < 10)fill();
	int random = rand() % (pos+1);
	if(pool[random]==preNumber)random = rand() % (pos + 1);
	int temp = pool[pos];
	pool[pos] = pool[random];
	pool[random] = temp;
	return pool[pos--];
}
