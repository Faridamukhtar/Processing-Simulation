#pragma once
#include "Linked List.h"
#include "Queue.h"
#include "processor.h"

#ifndef _FCFS_
#define _FCFS_

using namespace std;

class FCFS : public processor
{
	static Queue<SIGKILL> ListKill;
private:
	//friend class Scheduler;
	int fork_prob;
	LinkedList<process> RDYQueue;

public:
	FCFS(); //reads SIGKILL and fork_prob from input file
	~FCFS();
	bool AddSIGKILL(const SIGKILL& x); //calls this function when inputing file in scheduler
	bool iskill(SIGKILL & x, int timestep);
	virtual bool AddRDY(const process& x);
	virtual bool PopRDY(process& x);
	// process* fork(int& CT1, int& AT1); //PHASE 2
	virtual void ScheduleAlgo(Scheduler* SchPtr); //PHASE 2
	bool AddListKill(SIGKILL sig);
	virtual void print();
	virtual bool PeekRDY(process& x);
	//virtual bool FindRDY(int ID);
	virtual process* Fork(int forkprob, int &IDR, int timestep , int& forkedNum);
	virtual bool Delete(int killID, process& killed);
};
#endif