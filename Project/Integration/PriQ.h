#pragma once
#include "LNode.h"
#ifndef PRI_Q
#define PRI_Q
using namespace std;


template <class t>
class PriQ
{
private:
	LNode <t>* Front; // Pointer to first node
	LNode <t>* Rear; //Pointer to last node
	int count; // Current count of list items
public:
	PriQ(const PriQ& x)
	{
		int count = x.count;
		Front = new LNode <t>;
		Rear = new LNode <t>;
		if (x.Front())
		{
			*Front = *(x.Front);
			*Rear = *(x.Rear);
			LNode<t>* ptrmain = Front;
			LNode<t>* ptr = x.Front->getNext();
			while (ptr)
			{
				*(ptrmain->getNext()) = *ptr;
				ptr = ptr->getNext();
			}
			ptrmain->setNext(nullptr);
		}
		else
		{
			Front = Rear = NULL;
		}
	}

	void operator = (const PriQ& x)
	{
		int count = x.count;
		Front = new LNode <t>;
		Rear = new LNode <t>;
		if (x.Front())
		{
			*Front = *(x.Front);
			*Rear = *(x.Rear);
			LNode<t>* ptrmain = Front;
			LNode<t>* ptr = x.Front->getNext();
			while (ptr)
			{
				*(ptrmain->getNext()) = *ptr;
				ptr = ptr->getNext();
			}
			ptrmain->setNext(nullptr);
		}
		else
		{
			Front = Rear = NULL;
		}
	}
	PriQ()
	{
		Front = NULL;
		Rear = NULL;
		count = 0;

	}

	~PriQ()
	{
		clear();
	}

	bool isEmpty()
	{
		return Front == NULL;
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
			Front = Rear = NULL;
		}
		else
		{
			x = Front->getData();
			Front = Front->getNext();
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
			cout << ", ";
			ptr = ptr->getNext();
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

	bool Enqueue(const t& newEntry)
	{
		LNode<t>* node = new LNode<t>;
		if (node)
		{
			node->setData(newEntry);
			if (!Front)
			{
				Front = node;
				Rear = node;
				node->setNext(NULL);
				count++;
				return 1;
			}
			else
			{
				LNode<t>* temp = Front;
				if (node->getData() < temp->getData())
				{
					node->setNext(temp);
					Front = node;
					count++;
					return 1;
				}
				while (temp->getNext())
				{
					if (((temp->getNext()->getData()) > node->getData()) && (temp->getData() <= node->getData()))
					{
						node->setNext(temp->getNext());
						temp->setNext(node);
						count++;
						return 1;
					}
					temp = temp->getNext();
				}
				temp->setNext(node);
				node->setNext(NULL);
				Rear = node;
				count++;
				return 1;

			}
		}
		return 0;
	}

	int getCount()
	{
		return count;
	}

};

#endif
