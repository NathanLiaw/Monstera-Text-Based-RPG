#pragma once
#include "Monstera.h"

class DoublyLinkedNode
{
public:
	typedef DoublyLinkedNode Node;
	static Node NIL;

private:
	Monstera* value;
	Node* next;
	Node* previous;

public:
	// Default constructor
	DoublyLinkedNode()
	{
		value = nullptr;
		next = &NIL;
		previous = &NIL;
	}

	// Parameterised constructor
	DoublyLinkedNode(Monstera& aValue)
	{
		value = &aValue;
		next = &NIL;
		previous = &NIL;
	}

	// Add a node to the left of current node
	void prepend(Node* newNode)
	{
		newNode->next = this;

		if (this->previous != &NIL)
		{
			newNode->previous = this->previous;
			this->previous->next = newNode;
		}

		this->previous = newNode;
	}

	// Add a node to the right of current node
	void append(Node* newNode)
	{
		// 1. Point the new node's prev to me
		newNode->previous = this;

		// If next node exists
		if (this->next != &NIL)
		{
			// 2. New node's next become my original next node
			newNode->next = this->next;

			// 3. My original next node's previous node become the new node
			this->next->previous = newNode;
		}

		// 4. My next node point to new node
		this->next = newNode;
	}

	// Remove current node
	void remove()
	{
		// 1. My previous node's next become my current next node
		if (this->previous != &NIL)
		{
			this->previous->next = this->next;
		}

		// 2. My next node's previous become my current previous
		if (this->next != &NIL)
		{
			this->next->previous = this->previous;
		}

		// 3. Delete this node
		delete this;
	}

	// Return the Monstera type
	Monstera* getValue()
	{
		return value;
	}

	// Return the next node
	Node* getNext() const
	{
		return next;
	}

	// Return the previous node
	Node* getPrevious() const
	{
		return previous;
	}
};

