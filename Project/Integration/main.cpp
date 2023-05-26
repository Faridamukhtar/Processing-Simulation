#pragma once
#include "Scheduler.h"

using namespace std;

int main()
{

	Scheduler * S1 =new Scheduler;

	while (S1->TimeUp())
	{
		if (!S1->Schedule())
		{
			cout << "No Processors Available to Schedule."<<endl;
			break;
		}
	}

	delete S1;
	system("pause");
	return 0;
}


/* TRY DATA STRUCTURES
int x;
LinkedList<int> LL;
LL.insertLast(3);
LL.print();
LL.isEmpty();
LL.print();
LL.insertLast(1);
LL.insertLast(2);
LL.print();
LL.removeFirst(x);
LL.print();
LL.removeFirst(x);
LinkedList<int> *L2 = new LinkedList<int>(LL);
LinkedList<int>* L3 = new LinkedList<int>(LL);
cout << endl << x;
LL.print();
LL.clear();
cout << LL.removeFirst(x) << endl;
cout << endl << x;
delete L2;
delete L3;

system("pause");
*/