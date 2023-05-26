#pragma once
#include "RR.h"
#include"Scheduler.h"
using namespace std;


RR::RR(int timeslice_rr1)
{
	timeslice_rr = timeslice_rr1;
}

RR::~RR()
{

}

bool RR::AddRDY(const process& x)
{
	return RDYQueue.Enqueue(x);
}





bool RR::PopRDY(process& x)
{
	return RDYQueue.Dequeue(x);

}

void RR::print()
{
	cout << "[RR] " << RDYQueue.getCount() << " RDY :";
	RDYQueue.print();
}

bool RR::PeekRDY(process& x)
{
	return RDYQueue.peek(x);
}

void RR::ScheduleAlgo(Scheduler* SchPtr)
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
		if (state == 0)
		{
			state = 1;
		}
		else
		{
			count_rr = timeslice_rr;
			process f; //f represents the value to be removed from the ready queue
			RDYQueue.Dequeue(f);
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
		RunCount--;
		RUNP = NULL;
	}
	else if (RUNP)
	{
		RUNP->setTT(SchPtr->getTimestep());
		RUNP->calcTRT();
		RUNP->calcWT();
		if (RUNP->getWT() > SchPtr->get_MaxW() && !RUNP->getisChild() && !RUNP->getMigrate() && SchPtr->NEW_RDY_MIGRATE2(RUNP))
		{
			RunCount--;
			delete RUNP;
			RUNP = NULL;
		}
		else if (SchPtr->RUN_TRM_RR(RUNP, count_rr))
		{
			RunCount--;
			RUNP = NULL;
		}
		else
		{
			RUNP->IncCurrentCT();
			RUNP->DecRemCT();
		}
		count_rr--;

	}

}
