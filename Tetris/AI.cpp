#include "Ai.h"

AI::AI(bool _isTrain)
{
	isTrain = _isTrain;
	if (isTrain) {
		for (int i = 0; i < 10; i++) {
			gen[i].chromosome[0] = 0.305146;
			gen[i].chromosome[1] = 0.158340;
			gen[i].chromosome[2] = -0.421437;
			gen[i].chromosome[3] = -0.115076;
			/*for (int j = 0; j < 4; j++) {
				gen[i].chromosome[j] = (double)rand() / RAND_MAX - 0.5;
			}*/
			gen[i] = norm(gen[i]);
		}
		calcutateFitness(gen, 10);
		qsort(gen, totalGen, sizeof(Gen), compare);
	}
}

Gen AI::norm(Gen gen) {
	double t = 0;
	for (int j = 0; j < 4; j++) t += sqrt(gen.chromosome[j] * gen.chromosome[j]);
	for (int j = 0; j < 4; j++) gen.chromosome[j] /= t;
	return gen;
}

AI::~AI()
{
}

void AI::Init()
{
	Tetris::Init();
}

Move AI::bestMove(Gen &gen) {
	Move move;
 	double maxVal = -99999;
	Piece save = piece;
	for (int i = 0; i < 4; i++) {
		piece = save;
		for (int j = 0; j < i; j++)piece.rotate();
		while (check())piece.move(-1, 0);
		piece.cancel();
		Piece save2 = piece;
		for (int q = 0; ; q++) {
			piece.move(q, 0);
			if (!check())break;
			while (check())piece.move(0, 1);
			piece.cancel();
			for (int r = 0; r < 4; r++) board[piece.getBlock(r).y][piece.getBlock(r).x] = piece.getNumber();
			int clear = canClearLine();
			double val = estimateHeight() * gen.chromosome[0] + clear * gen.chromosome[1] + estimateHoles() * gen.chromosome[2] + estimateBumpiness() *gen.chromosome[3];
			for (int r = 0; r < 4; r++)	board[piece.getBlock(r).y][piece.getBlock(r).x] = 0;
			if (maxVal < val) {
				maxVal = val;
				move.rotateCount = i;
				move.moveCount = q;
				move.clearLine = clear;
			}
			piece = save2;
		}
	}
	piece = save;
	return move;
}

void AI::calcutateFitness(Gen *genList,int count)
{
	for (int i = 0; i < count; i++) {
		Init();
		while (true) {
			Move move = bestMove(genList[i]);
			genList[i].fitness += move.clearLine;
			for (int j = 0; j < move.rotateCount; j++)piece.rotate();
			while (check())piece.move(-1, 0);
			piece.cancel();
			for (int j = 0; j < move.moveCount; j++)piece.move(1, 0);
			drop();
			lineCheck();
			if (isOver()) break;
			newBlock();
		}
	}
}

int AI::estimateHeight() {
	int height = 0;
	for (int x = 0; x < BOARD_WEIGHT; x++) {
		for (int y = 0; y <BOARD_HEIGHT; y++) {
			if (board[y][x]) {
				height += y;
				break;
			}
		}
	}
	return height;
}

int AI::estimateHoles() {
	int x[BOARD_WEIGHT] = { 0, };
	int cnt = 0;
	for (int i = 0; i < BOARD_WEIGHT; i++) {
		bool start = false;
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (board[j][i])start = true;
			if (start && !board[j][i])cnt++;
		}
	}
	return cnt;
}

int AI::canClearLine() {
	int clearLine = 0;
	for (int i = BOARD_HEIGHT - 1, cnt = 0; i >= 0; cnt = 0, i--) {
		for (int x = 0; x < BOARD_WEIGHT; x++) {
			if (board[i][x])
				cnt++;
		}
		if (cnt == BOARD_WEIGHT) clearLine++;
	}
	return clearLine;
}

int AI::estimateBumpiness() {
	int bumpiness = 0;
	int y[BOARD_WEIGHT] = { 0, };
	for (int i = 0; i < BOARD_WEIGHT; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (board[j][i]) {
				y[i] = BOARD_HEIGHT - j;
				break;
			}
		}
	}
	for (int i = 0; i<BOARD_WEIGHT - 1; i++) bumpiness += abs(y[i] - y[i + 1]);
	return bumpiness;
}

void AI::nextGeneration()
{
	for (int i = 0; i < 3; i++) {
		Gen t = crossover(gen[tournamentSelect(0.7)], gen[tournamentSelect(0.7)]);
		if ((double)rand() / RAND_MAX < 0.3)
			t = mutate(t);
		tempgen[tempGenSize++] = t;
	}
	calcutateFitness(tempgen,tempGenSize);

	for (int i = 0; i < tempGenSize; i++) {
		gen[totalGen++] = tempgen[i];
	}
	tempGenSize = 0;
	qsort(gen, totalGen, sizeof(Gen), compare);
	totalGen = 10;

	printf("#%d max clear : %d, %f %f %f %f\n", genTime++, gen[0].fitness, gen[0].chromosome[0], gen[0].chromosome[1], gen[0].chromosome[2], gen[0].chromosome[3]);
	int tet = 0;
	for (int i = 0; i < totalGen; i++) {
		tet += gen[i].fitness;
	}
	printf("total fitness : %d \n", tet);

	
}

int AI::tournamentSelect(double offset) {
	int a = rand() % totalGen, b = rand() % totalGen;
	double r = (double)rand() / RAND_MAX;
	return (gen[a].fitness > gen[b].fitness) ? ((offset > r) ? a : b) : ((offset <= r) ? b : a);
}

Gen AI::crossover(Gen genA, Gen genB) {	
	Gen t;
	for (int i = 0; i < 4; i++) t.chromosome[i] = (genA.fitness +1)* genA.chromosome[i] + (genB.fitness +1)* genB.chromosome[i];
	return norm(t);
}
Gen AI::mutate(Gen gen) {
	double quantity = (double)rand()/RAND_MAX * 0.4 - 0.2;
	gen.chromosome[rand() % 4] += quantity;
	return gen;
}
int updateCount = 0;
void AI::update(double time)
{
	timer += time;

	nextGeneration();
	Init();
}

void AI::render(sf::RenderWindow & window)
{
	drawBackground(window);
	drawAllBlock(window);
	if (!isOver()) drawNowBlock(window);
}
