#pragma once
#include"LNode.h"

#ifndef _LINKED_LIST
#define _LINKED_LIST

using namespace std;

template < class t>
class LinkedList
{
private:
	LNode <t> * headPtr; // Pointer to first node
	LNode <t> * tailPtr; //Pointer to last node
	int count; // Current count of list items
	LNode<t>* Find(int data, LNode<t> ** previous) 	//Find Node ptr using data (ID in specific case)
	{
		LNode<t>* ptr = headPtr;
		*previous = ptr;
		while (ptr)
		{
			if (ptr->getData() == data)
			{
				return ptr;;
			}
			*previous = ptr;
			ptr=ptr->getNext();
		}
		previous = NULL;
		return NULL;

	}

public:
	int getCount()
	{
		return count;
	}


	LinkedList(const LinkedList & x)
	{
		int count = x.count;
		headPtr = new LNode<t>;
		tailPtr = new LNode<t>;
		if (x.headPtr)
		{
			*headPtr = *(x.headPtr);
			*tailPtr = *(x.tailPtr);
			LNode<t>* ptrmain = headPtr;
			LNode<t>* ptr = x.headPtr->getNext();
			while (ptr)
			{
				*(ptrmain->getNext()) = *ptr;
				ptr = ptr->getNext();
			}
			ptrmain->setNext(nullptr);
		}
		else
		{
			headPtr = nullptr;
			tailPtr = nullptr;
		}
	}

	void operator = (const LinkedList& x)
	{
		int count = x.count;
		headPtr = new LNode<t>;
		tailPtr = new LNode<t>;
		if (x.headPtr)
		{
			*headPtr = *(x.headPtr);
			*tailPtr = *(x.tailPtr);
			LNode<t>* ptrmain = headPtr;
			LNode<t>* ptr = x.headPtr->getNext();
			while (ptr)
			{
				*(ptrmain->getNext()) = *ptr;
				ptr = ptr->getNext();
			}
			ptrmain->setNext(nullptr);
		}
		else
		{
			headPtr = nullptr;
			tailPtr = nullptr;
		}
	}

	LinkedList()
	{
		headPtr = NULL;
		tailPtr = NULL;
		count = 0;

	}

	~LinkedList()
	{

		clear();
	}

	bool isEmpty()
	{
		return headPtr == NULL;
	}

	bool insertLast(const t& newEntry)
	{
		LNode<t>* node = new LNode<t>;
		if (node)
		{
			node->setData(newEntry);
			node->setNext(NULL);
			if (!headPtr)
			{
				headPtr = node;
				tailPtr = node;
			}
			else
			{
				tailPtr->setNext(node);
				tailPtr = node;
			}
			count++;
			return 1;
		}
		return 0;

	}

	bool removeFirst(t& x)
	{
		if (!headPtr)
		{
			return 0;
		}
		else if (headPtr == tailPtr)
		{
			x = headPtr->getData();
			delete headPtr;
			headPtr = tailPtr = NULL;
		}
		else
		{
			x = headPtr->getData();
			LNode<t> *temp = headPtr;
			headPtr = headPtr->getNext();
			delete temp;
		}
		count--;
		return 1;

	}



	bool Delete(int ID, t & deleted)
	{
 		LNode<t> ** previous= new LNode<t> *;
     	LNode<t> * ptr = Find(ID, previous);
		if (ptr)
		{
			deleted = ptr->getData();
			if (ptr == headPtr)
			{
				return removeFirst(deleted);
			}

			else
			{
				(*previous)->setNext(ptr->getNext());
				if (( * previous)->getNext() == NULL)
				{
					tailPtr == (*previous);
				}
				count--;
				return 1;
			}
		}
		return 0;

	}

	void clear()
	{
		LNode<t>* ptr = headPtr;
		while (ptr)
		{
			LNode<t>* temp = ptr;
			ptr = ptr->getNext();
			delete temp;
			temp = nullptr;
			count--;
		}

		headPtr = NULL;
		tailPtr = NULL;

	}

	void print() //print all data members
	{
		LNode<t>* ptr = headPtr;
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
		if (headPtr)
		{
			x = headPtr->getData();
			return 1;
		}
		else
		{
			return 0;
		}

	}

};

#endif