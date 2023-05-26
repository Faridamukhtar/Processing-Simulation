#pragma once
#include"LNode.h"
#ifndef QUEUE
#define QUEUE

using namespace std;

template < class t>
class Queue
{
private:
	LNode <t>* Front; // Pointer to first node
	LNode <t>* Rear; //Pointer to last nodez
	int count; // Current count of list items
public:

	Queue()
	{
		Front = NULL;
		Rear = NULL;
		count = 0;
	}

	Queue(const Queue& x)
	{
		count = x.count;
		LNode<t>* NodePtr = x.Front;
		if (!NodePtr) //x is empty
		{
			Front = Rear = nullptr;
			return;
		}
		//insert the first node
		LNode<t>* ptr = new LNode<t>;
		ptr->setData(NodePtr->getData());
		Front = Rear = ptr;
		NodePtr = NodePtr->getNext();
		//insert remaining nodes
		while (NodePtr)
		{
			LNode<t>* ptr = new LNode<t>;
			ptr->setData(NodePtr->getData());
			Rear->setNext(ptr);
			Rear = ptr;
			NodePtr = NodePtr->getNext();
		}
	}

void operator = (const Queue<t> & x)
{
	count = x.count;
	LNode<t> * NodePtr = x.Front;
	if (!NodePtr) //x is empty
	{
		Front = Rear = nullptr;
		return;
	}
	//insert the first node
	LNode<t>* ptr = new LNode<t>;
	ptr->setData(NodePtr->getData());
	Front = Rear = ptr;
	NodePtr = NodePtr->getNext();
	//insert remaining nodes
	while (NodePtr)
	{
		LNode<t>* ptr = new LNode<t>;
		ptr->setData(NodePtr->getData());
		Rear->setNext(ptr);
		Rear = ptr;
		NodePtr = NodePtr->getNext();
	}
}

	~Queue()
	{
		clear();
	}

	bool isEmpty()
	{
		return Front == NULL;
	}

	bool Enqueue(const t& newEntry)
	{
		LNode<t>* node = new LNode<t>;
		if (node)
		{
			node->setData(newEntry);
			node->setNext(NULL);
			if (!Front)
			{
				Front = node;
				Rear = node;
			}
			else
			{
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
		if (!Front)
		{
			return 0;
		}
		else if (Front == Rear)
		{
			x = Front->getData();
			delete Front;
			Front = Rear = NULL;
		}
		else
		{
			x = Front->getData();
			LNode<t> * temp = Front;
			Front = temp->getNext();
			delete temp;
		}
		count--;
		return 1;

	}



	void clear()
	{
		LNode<t>* ptr = Front;
		while (ptr)
		{
			LNode<t>* temp = ptr;
			ptr = ptr->getNext();
			delete temp;
			temp = NULL;
			count--;
		}

		Front = NULL;
		Rear = NULL;

	}

	void print() //print all data members
	{
		LNode<t>* ptr = Front;
		while (ptr)
		{
			ptr->PrintNode();
			ptr = ptr->getNext();
			if (ptr)
				cout << ", ";
		}
		cout << endl;
	}

	bool peek(t& x)
	{
		if (Front)
		{
			x = Front->getData();
			return 1;
		}
		else
		{
			return 0;
		}

	}

	int getCount()
	{
		return count;
	}



};

#endif