#pragma once
#include"processor.h"
#include"PriQ.h"

#ifndef _SJF_
#define _SJF_


class SJF: public processor
{
private:
	PriQ<process> RDYQueue;
public:
	SJF();
	~SJF();
	virtual bool AddRDY(const process& x);
	virtual bool PopRDY(process& x);
	void print();
	virtual bool PeekRDY(process& x);

	//virtual bool FindRDY(int ID);

	virtual void ScheduleAlgo(Scheduler* SchPtr); //PHASE 2

};

#endif
