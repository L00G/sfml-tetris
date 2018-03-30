#pragma once

#include "Tetris.h"

struct Gen {
	double chromosome[4] = { 0, };
	int fitness=0;
};

struct Move
{
	int rotateCount=0;
	int moveCount=0;
	int clearLine=0;
};

static int compare(const void *a, const void *b)
{
	return (*(Gen *)b).fitness - (*(Gen *)a).fitness;    // 내림차순
}

class AI : public Tetris
{
public:
	AI(bool _isTrain);
	Gen norm(Gen a);
	~AI();
	void Init();
	Move bestMove(Gen & gen);
	void calcutateFitness(Gen * genList, int count);
	int estimateHeight();
	int estimateHoles();
	int canClearLine();
	int estimateBumpiness();
	void nextGeneration();
	int tournamentSelect(double pivvvv);
	Gen crossover(Gen a, Gen b);
	Gen mutate(Gen a);
	virtual void update(double time) override;
	virtual void render(sf::RenderWindow & window) override;
public:
	bool isTrain = false;
	double timer=0, delay=0.0001;
	int repeatCount = 0;
	int genTime = 0;
	int nowGen = 0;
	int totalGen = 10;
	Gen tempgen[3];
	int tempGenSize = 0;
	Gen gen[13];
};

