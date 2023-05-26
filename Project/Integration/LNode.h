#pragma once
#include<iostream>
#ifndef _LNODE_
#define _LNODE_
using namespace std;


template<class t>
class LNode
{
private:
	t data;
	LNode <t> * Next;

public:
	LNode() //Constructor
	{
		Next= NULL;

	}

	~LNode() //Destructor
	{

	}

	//ListNode Setters and Getters

	void setData(const t& data1)
	{
		data = data1;
	}

	void setNext(LNode<t> * Next1)
	{
		Next = Next1;
	}

	t getData()
	{
		return data;
	}

	LNode<t> * getNext()
	{
		return Next;
	}

	void PrintNode()
	{
		cout << "Data: " << data;

	}


};
#endif
