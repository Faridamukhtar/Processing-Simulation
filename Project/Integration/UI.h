#pragma once
#include "FCFS.h"
#include"SJF.h"
#include"RR.h"

#ifndef UI_CLASS
#define UI_CLASS

class UI
{
private:
	Mode PrintMode;

public:

	UI();   //constructor to be initialized from scheduler 
	Mode SelectMode();
	Mode getMode();
	void print(int timestep1, processor** processorlist, Queue<process>* BLKL, Queue<process>* TRML, int pCount, int TCount, int BCount);
	~UI();
};

#endif 