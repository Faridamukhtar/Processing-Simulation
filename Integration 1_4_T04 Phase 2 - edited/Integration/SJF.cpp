#pragma once
#include "SJF.h"
#include "Scheduler.h"

using namespace std;



SJF::SJF()
{

}

SJF::~SJF()
{

}

bool SJF::AddRDY(const process& x)
{
	return RDYQueue.Enqueue(x);
}


bool SJF::PopRDY(process& x)
{
	return RDYQueue.Dequeue(x);
}

void SJF::print()
{
	cout << "[SJF] " << RDYQueue.getCount() << " RDY :";
	RDYQueue.print();
}

bool SJF::PeekRDY(process& x)
{
	return RDYQueue.peek(x);
}

void SJF::ScheduleAlgo(Scheduler* SchPtr)
{
	if (state == 1)
	{
		BusyTime++;
	}
	if (!RUNP && RDYQueue.isEmpty())
	{
		state = 0;
	}
	else if (!RDYQueue.isEmpty() && !RUNP)
	{
		if (state == 0)
		{
			state = 1;
		}
		else
		{
			process f;
			RDYQueue.Dequeue(f);
			dec_timer(f);
			RUNP = new process(f);
			RUNP->DecRemCT();
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
	else if (RUNP)
	{
		if (SchPtr->RUN_TRM(RUNP))
		{
			RUNP = NULL;
			RunCount--;
		}
		else
		{
			RUNP->IncCurrentCT();
			RUNP->DecRemCT();
  
		}
	}
}