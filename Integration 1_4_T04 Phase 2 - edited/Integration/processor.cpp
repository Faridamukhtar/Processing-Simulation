#pragma once
#include"Scheduler.h"
#include "processor.h"
#include <iostream>
using namespace std;

processor::processor()
{
	RUNP = NULL;
	state = false;
	BusyTime = 0;
	sum_ct = 0;
}

int processor:: RunCount;

processor::~processor()
{
	if (RUNP)
	{
		delete RUNP;
		RUNP = NULL;
	}
}


process* processor::getRUN()
{
	return RUNP;
}

void processor::EndRUN()
{
	RunCount--;
	delete RUNP;
	RUNP = NULL;

}


process* processor::Fork(int forkprob, int &IDR, int timestep, int& forkedNum)
{
	return NULL;
}



//might remove


bool processor::getState()
{
	return state;
}

int processor::getRunCount()
{
	return RunCount;
}

bool processor::Delete(int killID, process& killed)
{
	return 0;
}


void processor::inc_timer(process p)
{
	sum_ct += p.getCT();
}

void processor::dec_timer(process p)
{
	sum_ct -= p.getCT();
}

int processor::get_timer()
{
	return sum_ct;
}

bool processor::iskill(SIGKILL& x, int timestep)
{
	return 0;
}

int processor::getbusytime()
{
	return BusyTime;
}