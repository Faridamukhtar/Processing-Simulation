#pragma once
#include"FCFS.h"
#include"Scheduler.h"
#include <iostream>

using namespace std;

FCFS::FCFS()
{

}

Queue<SIGKILL> FCFS::ListKill;


FCFS::~FCFS()
{

}

bool FCFS::AddRDY(const process& x)
{
	return RDYQueue.insertLast(x);
}


bool FCFS::PopRDY(process& x)
{
	return RDYQueue.removeFirst(x);
}

bool FCFS::iskill(SIGKILL & x, int timestep)
{
	process killed;
	bool flag=0;
	if (ListKill.peek(x) && x.killTime==timestep)
	{
		ListKill.Dequeue(x);
		return 1;
	}
	return 0;
}

bool FCFS::AddSIGKILL(const SIGKILL& x)
{
	return ListKill.Enqueue(x);
}

bool FCFS::AddListKill(SIGKILL sig)
{
	return ListKill.Enqueue(sig);
}

void FCFS::print()
{
	cout << "[FCFS] " << RDYQueue.getCount() << " RDY :";
	RDYQueue.print();
}


bool FCFS::PeekRDY(process& x)
{
	return RDYQueue.peek(x);
}



process* FCFS::Fork(int forkprob, int &IDR, int timestep, int & forkedNum)
{
	process* forked;
	forked = RUNP->fork(forkprob, IDR, timestep);
	if (forked)
	{
		forkedNum++;
		IDR++;
		return forked;
	}
	return NULL;
}

bool FCFS::Delete(int killID, process& killed)
{
	return RDYQueue.Delete(killID, killed);
}


void FCFS::ScheduleAlgo(Scheduler* SchPtr)
{

	if (state == 1)
	{
		BusyTime++;
	}
	if (!RUNP && RDYQueue.isEmpty())
	{
		state = 0;
	}
	else if (!RUNP && !RDYQueue.isEmpty())
	{
		if (!state)
		{
			state = 1;
		}
		else
		{
			process f; //f represents the value to be removed from the ready queue
			RDYQueue.removeFirst(f);
			dec_timer(f);
			RUNP = new process(f);
			RunCount++;
			if (RUNP->getCT() == RUNP->getRemainingCT())
			{
				RUNP->calcRT(SchPtr->getTimestep());
			}
		}
	}
	else if (RUNP && SchPtr->RUN_BLK(RUNP))
	{
		RUNP = NULL;
		RunCount--;

	}
	else if (RUNP) //migration
	{
		RUNP->calcTRT();
		RUNP->calcWT();
		if (RUNP->getRemainingCT() < SchPtr->get_RTF() && !RUNP->getisChild() && !RUNP->getMigrate() && SchPtr->NEW_RDY_MIGRATE1(RUNP))
		{
			RunCount--;
			delete RUNP;
			RUNP = NULL;
		}
		else if (SchPtr->RUN_TRM(RUNP))
		{
			RunCount--;
			RUNP = NULL;
		}
		else
		{
			RUNP->IncCurrentCT();
			RUNP->DecRemCT();
			SchPtr->fork(RUNP);
		
		}
	}
}


