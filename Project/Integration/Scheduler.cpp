#pragma once
#include "Scheduler.h"
#include <iostream>
using namespace std;


Scheduler::Scheduler()
{
	UIptr = new UI;
	UIptr->SelectMode();
	timestep = -1;
	IORemaining = 0;
	input();
	min_ct = 0;
	max_ct = 0;
	WorkStlNum = 0;
	MigrateNumMAXW = 0;
	MigrateNumRTF = 0;

}

Scheduler::~Scheduler()
{
	if (UIptr->getMode() == SilentMode)
	{
		cout << "Simulation Ends.....Output File Created";
	}
	Output();
	cout << endl;
}

void Scheduler::input()
{
	ifstream in("Text6.txt");
	IO Iopairs1;
	string Braces1, BracesC, comma, IO_R, IO_D;
	in >> NF >> NS >> NR;
	LProcessors = new processor * [NF + NS + NR];
	in >> timeslice_rr;
	for (int i = 0; i < NF; i++)
	{
		FCFS* x = new FCFS;
		LProcessors[i] = x;
	}

	for (int i = NF; i < NF+NS; i++)
	{
		SJF* x = new SJF;
		LProcessors[i] = x;
	}
	for (int i = NF+NS; i < NF + NS + NR; i++)
	{
		RR* x = new RR(timeslice_rr);
		LProcessors[i] = x;
	}


	in >> rtf >> maxw >> stl >> fork_prob;
	in >> PCount;
	for (int i = 0; i < PCount; i++)
	{
		int AT, PID, CT, N;
		in >> AT >> PID >> CT >> N;
		process x (PID, AT, CT, NEW, N);

		for (int i = 0; i < N; i++)
		{
			in >> Braces1;
			in >> IO_R;
			in >> comma;
			in >> IO_D;
			in >> BracesC;
			int IO_R1 = stoi(IO_R);
			int IO_D1 = stoi(IO_D);
			Iopairs1.IO_D = IO_D1;
			Iopairs1.IO_R = IO_R1;
			x.setIOPairs(Iopairs1);
		}

		NEWL.Enqueue(x);
	}
	UniqueID = PCount;
	
	int time, ID;

	while (in >> time >> ID)
	{
		SIGKILL signal;
		signal.killTime = time;
		signal.killID = ID;
		FCFS n;
		n.AddSIGKILL(signal);
	}
}

bool Scheduler::TimeUp()
{
	while (PCount != TCount) //condition will happen at the end of the program 
	{
		timestep++;
		return 1;
	}
	return 0;
}


bool Scheduler::Schedule()
{
	if (NF + NS + NR > 0)
	{
		NEW_RDY();
		{
			for (int i = 0; i < NF + NS + NR; i++)
			{
				LProcessors[i]->ScheduleAlgo(this);
			}
		}
		if (NF > 0)
		{
			kill(LProcessors[0]);
		}
		BLK_RDY();
		if ((NF + NS + NR )> 1)
		{
			work_stl();
		}
		UIptr->print(timestep, LProcessors, &BLKL, &TRML, NF + NS + NR, TCount, BCount);
		Scheduled = 1;
		return 1;
	}
	else
	{
		Scheduled = 0;
		return 0;
	}
}


int Scheduler::getPCount()
{
	return PCount;
}




void Scheduler::fork(process* RUNP)
{
	process* forked;
	forked = RUNP->fork(fork_prob, PCount + 1, timestep);
	if (forked)
	{
		forkedNum++;
		PCount++;
		SHORTEST_FCFS(*forked);
		
	}
}

bool Scheduler::RUN_TRM(process* RUNP)
{
	RUNP->setTT(timestep);
	RUNP->calcTRT();
	RUNP->calcWT();
	if (RUNP->Terminate())
	{
		RUNP->setTT(timestep);
  		TRML.Enqueue(*RUNP);
		TCount++;
		delete RUNP;
		RUNP = nullptr;
		return 1;
	}
	return 0;
}

bool Scheduler::RUN_TRM_RR(process* RUNP, int countRR)
{
	RUNP->setTT(timestep);
	RUNP->calcTRT();
	RUNP->calcWT();
	if (RUNP->Terminate())
	{
		RUNP->setTT(timestep);
		TRML.Enqueue(*RUNP);
		TCount++;
		delete RUNP;
		RUNP = nullptr;
		return 1;
	}
	else if (countRR == 0)
	{
		int x, y, z, f;
		int Shortest = shortest_queue(x, y, z, f);
		LProcessors[Shortest]->AddRDY(*RUNP);
		delete RUNP;
		RUNP = NULL;
		return 1;
	}
	return 0;
}




bool Scheduler::RUN_BLK(process * RUNP)
{
	if (RUNP && !RUNP->getisChild())
	{
		IO x;
		Queue<IO> IOPairs = RUNP->getIOPairs();
		if (IOPairs.peek(x))
		{
			if (RUNP->getcurrentCT() == x.IO_R)
			{
				RUNP->DeqIO();
				RUNP->setcurrentIO(x);
				BLKL.Enqueue(*RUNP);
				BCount++;
				delete RUNP;
				RUNP = nullptr;
				return 1;
			}
		}
	}
	return 0;
}


void Scheduler::BLK_RDY()
{
	IO x;
	int z, y, f;
	process p;
	if (BLKL.peek(p))
	{
		x=p.getcurrentIO();
		IORemaining--;

		if (IORemaining == 0)
		{
			BLKL.Dequeue(p);
			BCount--;
			int Shortest = shortest_queue(min_ct, z, y, f);
			LProcessors[Shortest]->inc_timer(p);
			LProcessors[Shortest]->AddRDY(p);
		}
		else
		{
			IORemaining = x.IO_D;
		}
	}
	
}

void Scheduler::NEW_RDY()
{
	process x;
	int Shortest;
	int y,f, z;
	while (NEWL.peek(x) && x.getAT() == timestep)
	{
		NEWL.Dequeue(x);
		if (NF + NS + NR > 1)
		{
			Shortest = shortest_queue(min_ct, y, z, f);
		}
		else
		{
			Shortest = 0;
		}
		LProcessors[Shortest]->AddRDY(x);
		LProcessors[Shortest]->inc_timer(x);
	}
}

bool Scheduler::NEW_RDY_MIGRATE1(process* RUNP)
{
	int Shortest; //Replace with get Shortest RR (SEIF)
	int y, z;
	if (NF + NS + NR > 1)
	{
		RUNP->setMigrate();
		shortest_queue(min_ct, y, z, Shortest);
		LProcessors[Shortest]->AddRDY(*RUNP);
		LProcessors[Shortest]->inc_timer(*RUNP);
		MigrateNumRTF++;
		return 1;
	}
	return 0;
}

bool Scheduler::NEW_RDY_MIGRATE2(process* RUNP)
{
	int Shortest; //Replace with get Shortest SJF (SEIF)
	int y, z;
	if (NF + NS + NR > 1)
	{
		RUNP->setMigrate();
		shortest_queue(min_ct, y, Shortest, z);
		LProcessors[Shortest]->AddRDY(*RUNP);
		LProcessors[Shortest]->inc_timer(*RUNP);
		MigrateNumMAXW++;
		return 1;
	}
	return 0;
}

void Scheduler::SHORTEST_FCFS(process x) //forked
{
	int Shortest; //Replace with get Shortest FCFS (Farida)
	int y, z;
	shortest_queue(min_ct, Shortest, y, z);
	LProcessors[Shortest]->AddRDY(x);
	LProcessors[Shortest]->inc_timer(x);
}


int Scheduler::get_MaxW()
{
	return maxw;
}

int Scheduler::get_RTF()
{
	return rtf;
}


int Scheduler::shortest_queue(int& x, int &FCFS, int &RR, int &SJF)
{
	x = 100000000;
	FCFS = 0;
	SJF = NF;
	RR = NS+NF;
	int min_index = 0;
	int min_FCFS = 1000000000;
	int min_RR = 1000000000;
	int min_SJF = 1000000000;
	for (int i = 0; i < (NF + NS + NR); i++)
	{
		if (LProcessors[i]->get_timer() < x)
		{
			x = LProcessors[i]->get_timer();
			min_index = i;
		}
		if (i<NF && LProcessors[i]->get_timer() < min_FCFS)
		{
			min_FCFS = LProcessors[i]->get_timer();
			FCFS = i;
		}
		else if (i < NS+NF && LProcessors[i]->get_timer() < min_SJF)
		{
			min_SJF = LProcessors[i]->get_timer();
			SJF = i;
		}
		else if (i < NS + NF + NR && LProcessors[i]->get_timer() < min_RR)
		{
			min_RR = LProcessors[i]->get_timer();
			RR = i;
		}
	}
	return min_index;
}

int Scheduler::longest_queue(int& y)
{
	int max_index = 0;
	y = -1;
	for (int i = 0; i < (NF + NS + NR); i++)
	{
		if (LProcessors[i]->get_timer() > y)
		{
			y = LProcessors[i]->get_timer();
			max_index = i;
		}
	}
	return max_index;
}

void Scheduler::work_stl() 
{
	int f, y, z;
	int max_index = longest_queue(max_ct);
	int min_index = shortest_queue(min_ct, f, y, z);
	if (timestep % stl == 0)
	{
		process x;
		bool b = over_stl_lim();
		while (LProcessors[max_index]->PeekRDY(x) && !x.getisChild() && b && (x.getCT() != LProcessors[max_index]->get_timer()) && LProcessors[max_index]->get_timer() != LProcessors[min_index]->get_timer())
		{
			LProcessors[max_index]->PopRDY(x);
			LProcessors[max_index]->dec_timer(x);
			LProcessors[min_index]->AddRDY(x);
			LProcessors[min_index]->inc_timer(x);
			WorkStlNum++;
			int new_max;
			int new_min;
			int new_max_ct;
			int new_min_ct;
			new_max = longest_queue(new_max_ct);
			new_min = shortest_queue(new_min_ct, f, y, z);
			if ((new_min == max_index && new_max == min_index && abs(new_max_ct-max_ct) == abs(new_min_ct-min_ct)) || (new_max_ct==max_ct && new_min_ct==min_ct))
			{
				max_ct = new_max_ct;
				min_ct = new_min_ct;
				max_index = new_max;
				min_index = new_min;
				return;
			}
			max_ct = new_max_ct;
			min_ct = new_min_ct;
			max_index = new_max;
			min_index = new_min;
			LProcessors[max_index]->PeekRDY(x);
			b = over_stl_lim();
		}
		return;
	}
}

bool Scheduler::over_stl_lim()
{
	if (max_ct > 0)
	{
		float max_ctf = (float)max_ct;
		float min_ctf = (float)min_ct;
		float steal = ((max_ctf - min_ctf) / max_ctf); //multiplied by 100 as floating point comparison is not similar to integer comparison
		if (steal > 0.4)
		{
			return true;
		}     
		return false;
	}
	return false;
}

bool Scheduler::kill(processor * FCFS)
{
	SIGKILL x;
	process killed;
	while (FCFS->iskill(x, timestep))
	{
		for (int i = 0; i < NF; i++)
		{
			if (LProcessors[i]->getRUN()&& LProcessors[i]->getRUN()->getPID() == x.killID)
			{
 				killed = *(LProcessors[i]->getRUN());
				killed.killOrphan(LProcessors[i], timestep, this); //kills a different pointer  (orphan), pointer proble
				return 1;
			}
			else if (LProcessors[i]->Delete(x.killID, killed))
			{
				TRML.Enqueue(killed);
				TCount++;
				KillNum++;
				killed.killOrphan(LProcessors[i], timestep, this); //kills a different pointer  (orphan), pointer problem
				return 1;
			}
		}
	}
	return 0;
}


/*
void Scheduler::Terminate()
{
	RDYQueue.Delete(root->PID, processDeleted);
	TRML.Enqueue(processDeleted);
	TCount++;
}
*/

bool Scheduler::killOrphan(processor* FCFS, SIGKILL& x)
{
	process killed;
	for (int i = 0; i < NF; i++)
	{
		if (LProcessors[i]->getRUN() && LProcessors[i]->getRUN()->getPID() == x.killID)
		{
			LProcessors[i]->getRUN()->setTT(timestep);
			LProcessors[i]->getRUN()->calcTRT();
			LProcessors[i]->getRUN()->calcWT();
			TRML.Enqueue(*(LProcessors[i]->getRUN()));
			TCount++;
			LProcessors[i]->EndRUN();
			KillNum++;
			return 1;
		}
  		else if (LProcessors[i]->Delete(x.killID, killed))
		{
			killed.setTT(timestep);
			killed.calcTRT();
			killed.calcWT();
			TRML.Enqueue(killed);
			LProcessors[i]->dec_timer(killed);
			TCount++;
			KillNum++;
			return 1;
		}
	}
	return 0;
}

void Scheduler::Output()
{
	ofstream outputfile("TextFile1.txt");
	if (Scheduled)
	{
		float TRT = 0;
		float WT = 0;
		float RT = 0;
		outputfile << "TT       PID       AT       CT       IO_D       WT       RT       TRT" << endl;
		for (int i = 0; i < PCount; i++)
		{
			process x;
			TRML.Dequeue(x);
			TRT += (float)x.getTRT();
			RT += (float)x.getRT();
			WT += (float)x.getWT();
			outputfile << x.getTT() << "         " << x.getPID() << "         " << x.getAT() << "       " << x.getCT() << "          " << x.getIO_DT() << "         " << x.getWT() << "       " << x.getRT() << "        " << x.getTRT() << endl;
		}
		outputfile << endl << "Processes: " << PCount << endl << endl;
		outputfile << "Avg WT" << WT / PCount << "  Avg RT" << RT / PCount << "  Avg TRT: " << TRT / PCount << endl;
		float MigNumRTF = MigrateNumRTF;
		float MigNumMAXW = MigrateNumMAXW;
		float StlNum = WorkStlNum;
		outputfile << "Migration % :     RTF:" << (MigNumRTF / PCount) * 100 << " %         MAXW:" << (MigNumMAXW / PCount) * 100 << endl;
		outputfile << "Work Steal %:" << (StlNum / PCount) * 100 << " %" << endl;
		float forked = forkedNum;
		float killNum = KillNum;
		outputfile << "Forked Processes:" << (forked / PCount) * 100 << "%" << endl;
		outputfile << "Killed Processes:" << (killNum / PCount) * 100 << "%" << endl << endl;
		outputfile << "Processors: " << NF + NS + NR << " [" << NF << " FCFS  " << NS << " SJF  " << NR << "  RR ]" << endl;
		outputfile << "Processors Load" << endl;
		for (int i = 0; i < NF + NS + NR; i++)
		{
			outputfile << "P" << i + 1 << " = " << (LProcessors[i]->getbusytime() / TRT) * 100 << "%   ";
		}
		outputfile << endl << "Processor Utiliz:" << endl;
		float sum = 0;
		for (int i = 0; i < NF + NS + NR; i++)
		{
			float time = LProcessors[i]->getbusytime();
			outputfile << "P" << i + 1 << " = " << (time / timestep) * 100 << "%   ";
			sum += (time / timestep) * 100;
		}
		outputfile << endl << "Average Utilization: " << sum / (NF + NS + NR) << "%" << endl;
	}
	else
	{
		outputfile << "No Processors Found.";
	}
}


int Scheduler::getTimestep()
{
	return timestep;
}