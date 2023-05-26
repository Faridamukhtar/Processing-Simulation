#pragma once
#include "CirQ.h"
#include <iostream>

using namespace std;

template <class t>
CirQ<t>::CirQ()
{
	Rear = NULL;
	count = 0;
}

template <class t>
CirQ<t>::~CirQ()
{
	clear();
}

template <class t>
bool CirQ<t>::isEmpty()
{
	return count == 0;
}

template <class t>
bool CirQ<t>::Enqueue(const t& newEntry)
{
	LNode<t>* node = new LNode<t>;
	if (node)
	{
		node->setData(newEntry);
		if (!Rear)
		{
			Rear = node;
			node->setNext(Rear);
			Rear->setNext(Rear);
		}
		else
		{
			node->setNext(Rear->getNext());
			Rear->setNext(node);
		}
		count++;
		return 1;
	}
	return 0;

}

template <class t>
bool CirQ<t>::Dequeue(t& x)
{
	if (!Rear)
	{
		return 0;
	}
	else if (count==1)
	{
		x = Rear->getData();
		Rear = NULL;
	}
	else
	{
		x = Rear->getNext()->getData();
		Rear->setNext(Rear->getNext()->getNext());
	}
	count--;
	return 1;

}



template <class t>
void CirQ<t>::clear()
{
	LNode<t>* ptr;
	while (Dequeue(ptr))
	{
		delete ptr;
	}
	Rear = NULL;

}

template<class t>
void CirQ<t>::print() //print all data members
{
	LNode<t>* ptr = Rear;
	cout << count << " RDY:";
	for (int i = 0; i < count; i++)
	{
		cout << ptr->PrintNode() << ", ";
		ptr = ptr->getNext();
	}
	cout << endl;
}

template<class t>
t& CirQ<t>::peek()
{
	return Rear->getNext()->getData();
}
