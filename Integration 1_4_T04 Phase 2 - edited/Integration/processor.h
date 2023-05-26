#pragma once
#include "process.h"

#ifndef _PROCESSOR_
#define _PROCESSOR_

class Scheduler; //forward declaration 

class processor 
{
protected:
	static int RunCount;
	int ID;
	bool state; //Busy=1 or Idle=0
	float pLoad, pUtil;
	int BusyTime;
	int sum_ct;
	process* last;
	process * RUNP;//running process
public:
	processor();
	~processor();
	process* getRUN(); 
	int getRunCount();
	void EndRUN(); //Makes the necessary changes to end a running process (to either terminate or moving to a different list)
	virtual bool AddRDY(const process & x) = 0;
	virtual bool PopRDY(process& x) = 0;
	virtual bool PeekRDY(process& x) = 0;
	virtual void print() = 0;
	virtual bool iskill(SIGKILL& x, int timestep);
	virtual process* Fork(int forkprob, int &IDR, int timestep, int& forkedNum);
	virtual void ScheduleAlgo(Scheduler* SchPtr) = 0; //PHASE 2
	virtual bool Delete(int killID, process& killed);
	//bool ProcessCurrent(); //moves current ready process to run state if IDLE (Phase 1 simplified version of schedule algo)
	bool getState(); // can be removed (still unsure)
	int get_timer();
	virtual void inc_timer(process p);
	virtual void dec_timer(process p);
	int getbusytime();
};

#endif