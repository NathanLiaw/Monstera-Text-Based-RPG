#pragma once
#include "DoublyLinkedNode.h"

class DoublyLinkedNodeIterator
{
private:
	typedef DoublyLinkedNode Node;
	Node* current;

public:
	// Parameterised constructors
	DoublyLinkedNodeIterator(Node* start) : current(start) {}

	DoublyLinkedNodeIterator(Node& node) : current(&node) {}

	// Pre-increment operator
	DoublyLinkedNodeIterator& operator++()
	{
		current = current->getNext();
		return *this;
	}

	// Post-increment operator
	DoublyLinkedNodeIterator& operator++(int)
	{
		DoublyLinkedNodeIterator& temp = *this;
		++(*this);
		return temp;
	}

	// Increment the iterator to the previous node in the doubly linked list.
	// Returns a reference to the updated iterator.
	DoublyLinkedNodeIterator& operator--()
	{
		current = current->getPrevious();
		return *this;
	}

	// Post-decrement the iterator, creating a temporary iterator pointing to the original position.
	// Decrements the current iterator and returns the temporary iterator before the decrement.
	DoublyLinkedNodeIterator& operator--(int)
	{
		DoublyLinkedNodeIterator& temp = *this;
		--(*this);
		return temp;
	}

	// Compare two iterators for equality based on their current node pointers.
	bool operator==(const DoublyLinkedNodeIterator& other) const
	{
		return current == other.current;
	}

	// Compare two iterators for inequality based on their current node pointers.
	bool operator!=(const DoublyLinkedNodeIterator& other) const
	{
		return current != other.current;
	}

	// Dereference the iterator, returning a pointer to the Monstera object it currently points to.
	Monstera* operator*() const
	{
		return current->getValue();
	}

	// Get the current node of the iterator.
	Node* getCurrent()
	{
		return current;
	}

	// Return an iterator pointing to the current node.
	DoublyLinkedNodeIterator begin()
	{
		return DoublyLinkedNodeIterator(current);
	}

	// Return an iterator pointing to the end of the list (NIL node).
	DoublyLinkedNodeIterator end()
	{
		return DoublyLinkedNodeIterator(Node::NIL);
	}

};