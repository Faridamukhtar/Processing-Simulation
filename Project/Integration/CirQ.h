#pragma once
#ifndef _CIRQ_
#define _CIRQ_

#include"LNode.h"

using namespace std;

template < class t>
class CirQ
{
private:
	LNode <t>* Rear; //Pointer to last node
	int count; // Current count of list items
public:

	int getCount()
	{
		return count;
	}

	CirQ(const CirQ& x)
	{
		int count = x.count;
		Rear = new LNode <t>;
		if (x.Rear)
		{
			*Rear = *(x.Rear);
			LNode<t>* ptrmain = Rear;
			LNode<t>* ptr = x.Rear();
			for (int i = 1; i < count; i++)
			{
				*(ptrmain->getNext()) = *ptr;
				ptr = ptr->getNext();

			}
			ptrmain->setNext(nullptr);
		}
		else
		{
			Rear = NULL;
		}
	}

	void operator = (const CirQ& x)
	{
		int count = x.count;
		Rear = new LNode <t>;
		if (x.Rear)
		{
			*Rear = *(x.Rear);
			LNode<t>* ptrmain = Rear;
			LNode<t>* ptr = x.Rear();
			for (int i = 1; i < count; i++)
			{
				*(ptrmain->getNext()) = *ptr;
				ptr = ptr->getNext();

			}
			ptrmain->setNext(nullptr);
		}
		else
		{
			Rear = NULL;
		}
	}




	CirQ()
	{
		Rear = NULL;
		count = 0;
	}

	~CirQ()
	{
		clear();
	}

	bool isEmpty()
	{
		return count == 0;
	}

	bool Enqueue(const t& newEntry)
	{
		LNode<t>* node = new LNode<t>;
		if (node)
		{
			node->setData(newEntry);
			if (!Rear)
			{
				Rear = node;
				node->setNext(Rear);
			}
			else
			{
				node->setNext(Rear->getNext());
				Rear->setNext(node);
				Rear = node;
			}
			count++;
			return 1;
		}
		return 0;

	}

	bool Dequeue(t& x)
	{
		if (!Rear)
		{
			return 0;
		}
		else if (count == 1)
		{
			x = Rear->getData();
			delete Rear;
			Rear = NULL;
		}
		else
		{

			LNode<t>* temp = Rear->getNext();
			x = temp->getData();
			Rear->setNext(temp->getNext());
			delete temp;
		}
		count--;
		return 1;

	}



	void clear()
	{
		t x;
		while (Dequeue(x))
		{
		}
		Rear = NULL;

	}

	void print() //print all data members
	{
		if (Rear)
		{
			LNode<t>* ptr = Rear->getNext();
			for (int i = 0; i < count; i++)
			{
				ptr->PrintNode();
				ptr = ptr->getNext();
				if (i != (count-1))
					cout << " , ";
			}
		}
		cout << endl;
	}

	bool peek(t& x)
	{
		if (Rear)
		{
			x = Rear->getNext()->getData();
			return 1;
		}
		else
		{
			return 0;
		}

	}


};

#endif