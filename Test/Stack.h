#pragma once
#include <iostream>
#include "List.h"
using namespace std;

// A stack class that uses a linked list to store elements
class Stack
{
private:
	List list; 
	int limit; 

public:
	// Default constructor
	Stack()
	{
		limit = 50;
	}

	// Function to check if the stack is empty.
	bool isEmpty() { return list.isEmpty(); }

	// Function to get the current size of the stack.
	int size() { return list.size(); }

	// Getter for the stack's size limit.
	int getLimit() const
	{
		return limit;
	}

	// Setter for the stack's size limit.
	void setLimit(int limit)
	{
		this->limit = limit;
	}

	// Function to push a Monstera onto the stack.
	void Push(Monstera& value)
	{
		if (list.size() <= limit)
		{
			list.push_back(value);
		}
	}

	// Function to pop a Monstera from the stack.
	// Returns a pointer to the popped Monstera.
	Monstera* Pop()
	{
		if (list.size() > 0)
		{
			return list.pop_back();
		}
	}

	// Destructor
	~Stack()
	{
		// No need to do anything because list has its own destructor implementation
	}
};
