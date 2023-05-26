#pragma once
#ifndef _RR_
#define _RR_
#include"processor.h"
#include"CirQ.h"

class RR : public processor
{
private:
	CirQ<process> RDYQueue;
	int timeslice_rr;
	int count_rr;


public:
	RR(int timeslice_rr1);
	~RR();
	virtual bool AddRDY(const process& x);
	virtual bool PopRDY(process& x);
	void print();
	virtual bool PeekRDY(process& x);


	//virtual bool FindRDY(int ID);
	virtual void ScheduleAlgo(Scheduler* SchPtr); //PHASE 2

};

#endif