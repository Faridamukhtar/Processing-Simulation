#pragma once
#include "UI.h"
#include "SJF.h"
#include "RR.h"
#include"FCFS.h"
#include <fstream>


#ifndef _SCHEDULER_
#define _SCHEDULER_

class Scheduler
{
private:
	UI* UIptr;
	int timestep;
	int IORemaining;
	int UniqueID;
	int MigrateNumRTF;
	int MigrateNumMAXW;
	int WorkStlNum;
	int NF, NS, NR, timeslice_rr, rtf, maxw, stl, fork_prob;  //might remove fork prob and timeslice_rr
	int PCount; //total Number of Processes 
	int TCount; //Number of Processes in TRM list
	int BCount; //Number of Processes in BLK list
	processor ** LProcessors; //arranged in order: first X places: FCFS, second Y places: SJF, third Z places: RR
	Queue<process> NEWL;  //process created from input file will be loaded to this list
	Queue<process> BLKL; //processes waiting for IO
	Queue<process> TRML; //processes to be terminated
	//int currentP; // for phase 1, to know current processor, max =PCount
	int forkedNum, KillNum;
	int max_ct;
	int min_ct;
	bool Scheduled;
	//int ohprob;
public:
	Scheduler();
	~Scheduler();
//	void Simulate();
//	void randomize(processor* x);
	bool Schedule();
	int getPCount();
	void input(); //reads input from file and initializes processes
	bool TimeUp(); //Increments time step
	void Output();
	//Phase 2 (to be adjusted)
	//void AllocFork(); //adds forked process to shortest FCFS queue (PHASE 2)
	//void output(); //creates output file
	void fork(process* RUNP);
	bool RUN_TRM(process* RUNP);
	bool RUN_BLK(process* RUNP);
	void BLK_RDY();
	bool RUN_TRM_RR(process* RUNP, int countRR);
	void NEW_RDY();
	bool NEW_RDY_MIGRATE1(process* RUNP);
	bool NEW_RDY_MIGRATE2(process* RUNP);
	void SHORTEST_FCFS(process x);
	int shortest_queue(int&x, int& FCFS, int& RR, int& SJF); //x will be replaced by min_ct in function call
	int longest_queue(int& y); //y will be replaced by max_ct in function call
	void work_stl();
	bool over_stl_lim(); // done
	int get_MaxW();
	int get_RTF();
	bool kill(processor* FCFS);
	bool killOrphan(processor* FCFS, SIGKILL& x);
	int getTimestep();
	//void Terminate();
};

#endif