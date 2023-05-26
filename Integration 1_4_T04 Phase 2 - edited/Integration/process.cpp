#pragma once
#include "process.h"
#include "Scheduler.h"
#include "processor.h"
#include <iostream>
using namespace std;

process::process(int PID1, int AT1, int CT1, ProcessState state1, int N=0)
{
	PID = PID1;
	AT = AT1;
	IO_DT = 0;
	CT = CT1;
	RT = 0;
	currentCT = 0;
	RemainingCT = CT;
	state = state1;
	isMigrated = 0;
	NumOfIO=N;
}

process::process()
{

}


process::~process()
{

}




void process::setPID(int PID1) 
{
	PID = PID1;
}

void process::setCT(int CT1)
{
	CT = CT1;
}

void process::setAT(int AT1)
{
	AT = AT1;
}

void process::setPS(ProcessState ProcessState1)
{
	state = ProcessState1;
}

void process::setIOnum(int N)
{
	NumOfIO = N;
}

void process::setisChild(bool child)
{
	isChild = child;
}

void process::setRT(int RT1)
{
	RT = RT1;
}

/* (MIGHT NEED)
void process::setIOPairs(int IO_R1, int IO_D1)
{
	IO IOnew;
	IOnew.IO_R = IO_R1;
	IOnew.IO_D = IO_D1;
	IOPairs.Enqueue(IOnew);
}
*/

void process::setIOPairs(IO IOPairs1)
{
	IOPairs.Enqueue(IOPairs1);
}

void process:: DeqIO()
{
	IO x;
	IOPairs.Dequeue(x);
}

void process::setcurrentIO(IO currentIO1)
{
	currentIO = currentIO1;
}

void process::setTT(int TT1)
{
	TT = TT1;
}


int process::getTT()
{
	return TT;
}

int process::getTRT()
{
	return TRT;
}

int process::getPID() 
{
	return PID;
}

int process::getAT()
{
	return AT;
}
int process::getRT()
{
	return RT;
}
int process::getCT()
{
	return CT;
}
int process::getcurrentCT()
{
	return currentCT;
}

int process::getIONum()
{
	return NumOfIO;
}

IO process::getcurrentIO()
{
	return currentIO;
}

ProcessState process::getState()
{
	return state;
}

Queue<IO> process::getIOPairs()
{
	return IOPairs;
}

bool process::getisChild()
{
	return isChild;
}




void process::DecRemCT()
{
	RemainingCT--;
}




bool process::operator>(process x)
{
	return (CT > x.CT);
}


bool process::operator<(process x)
{
	return (CT < x.CT);
}


bool process::operator==(process x)
{
	return (CT == x.CT);
}


bool process::operator>=(process x)
{
	return (CT >= x.CT);
}

bool process::operator <=(process x)
{
	return (CT <= x.CT);
}

bool process::operator ==(int x)
{
	return (PID==x);
}

ostream& operator  << (ostream& out, process p)
{
	out << p.PID;
	return out;
}




//PHASE 2

void process::calcTRT()
{
	TRT = TT - AT;
}

void process::calcWT()
{
	WT = TRT - currentCT;
}

void process::calcRT(int timestep)
{
	RT = timestep - AT;
}


void process::killOrphan(processor* FCFS, int timestep, Scheduler* SchPtr)
{
	killOrphan(this, FCFS, timestep, SchPtr);
}

void process::killOrphan(process* root, processor* FCFS, int timestep, Scheduler* SchPtr)
{
 	if (!root)
	{
		return;
	}
	if (root->Lchild)
	{
		killOrphan(root->Lchild, FCFS, timestep, SchPtr);
	}
	if (root->Rchild)
	{
		killOrphan(root->Rchild, FCFS, timestep, SchPtr);
	}
	SIGKILL x;
	x.killID = root->PID;
	x.killTime = timestep;
	SchPtr->killOrphan(FCFS, x);

}


process* process::fork(int forkprob, int ID, int timestep)
{
	int random = rand() % 100;
	if (random <= forkprob && (!Rchild || !Lchild))
	{
		if (Lchild)
		{
			Rchild = new process(ID, timestep, RemainingCT, RDY, 0);
			Rchild->setisChild(1);
			return Rchild;
		}
		Lchild = new process(ID, timestep, RemainingCT, RDY, 0);
		Lchild->setisChild(1);
		return Lchild;
	}
	return NULL;
}

void process::IncCurrentCT()
{
	currentCT++;
}

bool process::Terminate()
{
	return CT == currentCT;
}

int process::getWT()
{
	return WT;
}

int process::getRemainingCT()
{
	return RemainingCT;
}

int process::getIO_DT()
{
	return IO_DT;
}

void process::setMigrate()
{
	isMigrated = 1;
}

bool process::getMigrate()
{
	return isMigrated;
}