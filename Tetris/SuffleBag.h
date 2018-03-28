#ifndef _SUFFLE_BAG_H_
#define _SUFFLE_BAG_H_

#include<random>
#include<map>

namespace SuffleBag {
	static const std::map<std::string, int> piecesPercent = { { "I",6 },{ "Z",18 },{ "ZR",18 },{ "T",15 },{ "L",18 },{ "LR",18 },{ "O",6 } };

	void fill();
	void add(int nubmer, int count);
	int next();
	static char pool[100];
	static int pos=-1, preNumber=-1;
}

#endif

