#pragma once
#include "enum.h"
#include <iostream>
#include "Queue.h"
#include "Linked List.h"

#ifndef _PROCESS_
#define _PROCESS_

using namespace std;

class processor;

class Scheduler;

class process
{
	/*
		PID: unique identifier(ID)
		Arrival Time(AT)
		Response Time(RT)
		CPU Time
		Termination Time(TT)
		Turnaround Duration(TRT)
		Waiting Time(WT)
		Process State : NEW, RDY, RUN, BLK, TRM, ORPH
		I / O Request Time
	*/
private:
	int PID, AT, RT, CT, TT, TRT, WT, RemainingCT, currentCT, NumOfIO;
	IO currentIO;
	Queue<IO> IOPairs;
	process* Rchild;
	process* Lchild;
	bool isChild;
	ProcessState state;
	int IO_DT;
	bool isMigrated;
	bool processed;  //checks if processed in current time step
	void killOrphan(process* root, processor* FCFS, int timestep, Scheduler* SchPtr);
public:
	process(int PID1, int AT1, int CT1, ProcessState state1, int N); //non-default constructor
	process(); //default constructor
	~process(); //destructor
	void DecRemCT(); // Incrementing current computation time in progress
	void DeqIO();


	//setters (Phase 1)
	void setPID(int PID1);
	void setAT(int AT1);
	void setCT(int CT1);
	void setcurrentIO(IO currentIO1);
	//void setIOPairs(int IO_R1, int IO_D1); (MIGHT NEED)
	void setPS(ProcessState ProcessState1);
	void setIOPairs(IO IOPairs);
	void setIOnum(int N);
	void setTT(int TT1);
	void setRT(int RT1);
	void setisChild(bool child);

	//getters
	int getPID();
	int getTT();
	int getTRT();
	int getIO_DT();
	int getAT();
	int getRT();
	int getCT();
	int getcurrentCT();
	int getIONum();
	int getWT();
	IO getcurrentIO();
	void calcRT(int timestep);
	int getRemainingCT();
	bool getMigrate();

	Queue<IO> getIOPairs();
	ProcessState getState();
	bool getisChild();


//operator overloading

	bool operator >(process x);
	bool operator <(process x);
	bool operator >=(process x);
	bool operator <=(process x);
	bool operator ==(process x);
	bool operator ==(int x);
	friend 	ostream& operator  << (ostream& out, process p);

// PHASE 2
	process* fork(int forkprob, int ID, int timestep); //forking process implementation
	void killOrphan(processor* FCFS, int timestep, Scheduler* SchPtr); //kill Orpahn
	void IncCurrentCT();
	bool Terminate();
	void calcWT();
	void calcTRT();
	void setMigrate();


	//int getTT();
	//int getWT();
	//int getTRT();
	//process* getChild();


};

#endif