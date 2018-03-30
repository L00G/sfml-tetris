#ifndef _SUFFLE_BAG_H_
#define _SUFFLE_BAG_H_

#include<cstdlib>
#include<time.h>
#include<map>

namespace ShuffleBag {
	static const std::map<std::string, int> piecesPercent = { { "I",15 },{ "Z",16 },{ "ZR",16 },{ "T",16 },{ "L",16 },{ "LR",16 },{ "O",4 } };

	void fill();
	void add(int nubmer, int count);
	int next();
	static char pool[100];
	static int pos=-1, preNumber=-1;
}

#endif

