#include <fstream>
#include <iostream>
#include "Ai.h"

std::ofstream writeFile;

AI::AI()
{
	traning = false;
	
	generation = new Gen();

	std::ifstream  readFile("offset.txt");
	if (readFile.is_open()) {
		readFile >> generation->chromosome[0] >> generation->chromosome[1]>> generation->chromosome[2]>>generation->chromosome[3];
		readFile.close();
	}
	
	timer = 0;
	delay = 0.3;
}

AI::AI(int _generationNumber, int _numberRepetitions) {
	traning = true;
	
	numberRepetitions = _numberRepetitions;
	generationNumber = _generationNumber;
	nowRepetitions = 0;

	generation = new Gen[generationNumber*1.3 + 5];
	offspring = new Gen[generationNumber*0.3 + 5];

	for (int i = 0; i < generationNumber; i++) {
		for (int j = 0; j < 4; j++)	generation[i].chromosome[j] = (double)rand() / RAND_MAX - 0.5;
		generation[i] = norm(generation[i]);
	}
	calcutateFitness(generation, generationNumber);
	qsort(generation, generationNumber, sizeof(Gen), compare);

	writeFile.open("log.txt", std::ofstream::app | std::ofstream::ate);
	if (writeFile.is_open()) {
		writeFile << "----Traing Result----" << std::endl;
		writeFile << "Setting  [ numberRepetitions : "<<numberRepetitions<<", generationNumber : "<<generationNumber<<" ]" << std::endl;
		writeFile << "#Case Number:" << nowRepetitions << " Max Clear Line Count : " << generation[0].fitness << "   Result : " << generation[0].chromosome[0] << " " << generation[0].chromosome[1] << " " << generation[0].chromosome[2] << " " << generation[0].chromosome[3] << std::endl;
	}
}

AI::~AI()
{
	delete[]generation;
	delete[]offspring;
}

void AI::Init()
{
	Tetris::Init();
}

Gen AI::norm(Gen gen) {
	double t = 0;
	for (int j = 0; j < 4; j++) t += sqrt(gen.chromosome[j] * gen.chromosome[j]);
	for (int j = 0; j < 4; j++) gen.chromosome[j] /= t;
	return gen;
}

Move AI::bestMove(Gen &gen) {
	Move move;
 	double maxVal = -INT_MAX;
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
	int maxOffspring = generationNumber * 0.3;
	for (int i = 0; i < maxOffspring; i++) {
		Gen t = crossover(generation[tournamentSelect(0.7)], generation[tournamentSelect(0.7)]);
		if ((double)rand() / RAND_MAX < 0.3)
			t = mutate(t);
		offspring[i++] = t;
	}
	calcutateFitness(offspring, maxOffspring);

	for (int i = 0; i < maxOffspring; i++) {
		generation[generationNumber+i] = offspring[i];
	}

	int maxfitness = generation[0].fitness;
	qsort(generation, generationNumber + maxOffspring, sizeof(Gen), compare);
	if (maxfitness < generation[0].fitness) {	
		if (writeFile.is_open()) {
			writeFile << "#Case Number:" << nowRepetitions << " Max Clear Line Count : " << generation[0].fitness << "   Result : " << generation[0].chromosome[0] << " " << generation[0].chromosome[1] << " " << generation[0].chromosome[2] << " " << generation[0].chromosome[3] << std::endl;
		}
	}
	printf("#Case Number: %d max clear : %d, Result : %f %f %f %f\n", (nowRepetitions++)+1, generation[0].fitness, generation[0].chromosome[0], generation[0].chromosome[1], generation[0].chromosome[2], generation[0].chromosome[3]);
	
	int total = 0;
	for (int i = 0; i < generationNumber; i++) {
		total += generation[i].fitness;
	}
	printf("total fitness : %d \n", total);
}

int AI::tournamentSelect(double offset) {
	int a = rand() % generationNumber, b = rand() % generationNumber;
	double r = (double)rand() / RAND_MAX;
	return (generation[a].fitness > generation[b].fitness) ? ((offset > r) ? a : b) : ((offset <= r) ? b : a);
}

Gen AI::crossover(Gen genA, Gen genB) {	
	Gen t;
	for (int i = 0; i < 4; i++) t.chromosome[i] = (genA.fitness +1)* genA.chromosome[i] + (genB.fitness +1)* genB.chromosome[i];
	return norm(t);
}

Gen AI::mutate(Gen gen) {
	for (int i = 0; i < 4; i++) {
		double quantity = (double)rand() / RAND_MAX * 0.2 - 0.2;
		gen.chromosome[i] += quantity;		
	}
	return gen;
}

void AI::update(double time)
{
	timer += time;

	if (traning) {
		while (nowRepetitions < numberRepetitions) {
			nextGeneration();
		}
		writeFile << "If you want test, Copy this to 'offset.txt' : " << generation[0].chromosome[0] << " " << generation[0].chromosome[1] << " " << generation[0].chromosome[2] << " " << generation[0].chromosome[3] << std::endl;
		writeFile << std::endl;
		writeFile.close();
	}
	else {
		lineCheck();
		if (!isOver()) {
			newBlock();

			while (timer > delay) {
				Move move = bestMove(*generation);
				generation->fitness += move.clearLine;
				for (int j = 0; j < move.rotateCount; j++)piece.rotate();
				while (check())piece.move(-1, 0);
				piece.cancel();
				for (int j = 0; j < move.moveCount; j++)piece.move(1, 0);
				drop();
				timer -= delay;
				delay = .3 / speedState;
			}
		}
		else {
			gameOver(timer / 0.1);
			if (timer > 2)Init();
		}
	}
}

void AI::render(sf::RenderWindow & window)
{
	if (!traning) {
		drawBackground(window);
		drawAllBlock(window);
		if (!isOver()) {
			drawNowBlock(window);
		}
	}
}
