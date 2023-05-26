#pragma once
#include "UI.h"
#include<Windows.h>
#include<iostream>

using namespace std;

UI::UI()
{

}

UI::~UI()
{

}

Mode UI::SelectMode()
{
	int ModeNum;
	cout << "Select Simulation Mode (1->3):" << endl;
	cin >> ModeNum;
	while (ModeNum <= 0 || ModeNum > 3)
	{
		cout << "Invalid. Select a Valid Simulation Mode (1->3):";
		cin >> ModeNum;
	}
	switch (ModeNum)
	{
	case 1:
		PrintMode = InteractiveMode;
		break;
	case 2:
		PrintMode = StepByStep;
		break;
	case 3:
		PrintMode = SilentMode;
		cout << "Silent Mode................Simulation Starts..." << endl;
		break;
	}
	return PrintMode;
}

Mode UI::getMode()
{
	return PrintMode;
}

void UI::print(int timestep1, processor** processorlist, Queue<process>* BLKL, Queue<process>* TRML, int pCount, int TCount, int BCount)
{
	if (PrintMode != SilentMode)
	{
		cout << "Current Timestep:" << timestep1 << endl;
		cout << endl;
		cout << "RDY Processes" << endl;
		for (int i = 0; i < pCount; i++)
		{
			cout << "processor " << i + 1 << " ";
			processorlist[i]->print();
			cout << endl;
		}

		cout << endl << "BLK Processes" << endl;
		cout << BCount << " BLK : ";
		BLKL->print();
		cout << endl;
		cout << "RUN Processes" << endl;
		int RCount = processorlist[1]->getRunCount();
		cout << RCount << " RUN : ";
		for (int i = 0; i < pCount; i++)
		{
			if (processorlist[i]->getRUN())
				cout << *(processorlist[i]->getRUN()) << "(P" << i + 1 << ") ";
		}
		cout << endl << endl;
		cout << "TRM Processes" << endl;
		cout << TCount << " TRM : ";
		TRML->print();
		cout << endl;
		switch (PrintMode)
		{
		case InteractiveMode:
			system("pause");
			cout << endl << "//////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;;
			cout << endl << endl;
			break;

		case StepByStep:
			Sleep(1000);
			cout << endl << "//////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;;
			cout << endl << endl;
		}
	}
	else
	{
		return;
	}

}

//void UI::output()
//{
//
//	ifstream out("output.txt");
//	out << TT << PID << AT << CT << IO_D << WT << RT << TRT;
//	out << "Processes" << n;
//	out << "Avg WT:" << WT << " " << "Avg RT:" << RT << " " << "Avg TRT:" << TRT;      //calculate AVG
//	
//
//} *Phase2*

/* PHASE 2
int UI::display()
{
	int x;
	cout << "Please select the program mode " << endl;   // asks the user to select the program mode, for phase 1 we only have Interactive Mode
	cout << "Press 1 for InteractiveMode, 2 for StepByStep, 3 for SilentMode " << endl;
	cin >> x;
	return x;

}
*/