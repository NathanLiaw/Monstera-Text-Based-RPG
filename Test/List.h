#pragma once
#include "DoublyLinkedNode.h"
#include "DoublyLinkedNodeIterator.h"
#include <iostream>
using namespace std;

class List
{
private:
	typedef DoublyLinkedNode Node;
	Node* head;
	Node* last;
	int count;

public:
	typedef DoublyLinkedNodeIterator Iterator;

	// Default constructor
	List() : head(&(Node::NIL)), last(&(Node::NIL)), count(0) {}

	// Parameterised constructor
	List(Node* headNode, Node* lastNode) : head(headNode), last(lastNode), count(1) {}

	// Destructor
	~List()
	{
		Iterator it = getIterator();
		while (it != it.end())
		{
			Node* toDelete = it.getCurrent();
			toDelete->remove();
			++it;
		}
	}

	// Return bool if list is empty
	bool isEmpty() const { return count == 0; }

	// Return list size
	int size() const { return count; }

	// Add an element to the end (most right) of the list
	void push_back(Monstera& value)
	{
		Node* newNode = new Node(value);

		if (head == &(Node::NIL)) {
			head = newNode;
			last = newNode;
		}
		else {
			last->append(newNode);
			last = newNode;
		}
		++count;
	}

	// Add an element to the beginning (most left) of the list
	void push_front(Monstera& value)
	{
		Node* newNode = new Node(value);

		if (head == &(Node::NIL)) {
			head = newNode;
			last = newNode;
		}
		else {
			head->prepend(newNode);
			head = newNode;
		}
		++count;
	}

	// Remove the element from the head (most left)
	void pop_front()
	{
		Node* temp = head;

		if (head != &(Node::NIL))
		{
			Node* toDelete = head;
			head = head->getNext();
			temp = toDelete;
			toDelete->remove();
			--count;

			if (head == &(Node::NIL))
			{
				last = &(Node::NIL);
			}
		}
	}

	// Remove the element from the tail (most right)
	Monstera* pop_back()
	{
		Node* temp = last;
		Monstera* value = temp->getValue();
		if (last != &(Node::NIL))
		{
			Node* toDelete = last;
			last = last->getPrevious();
			temp = toDelete;
			toDelete->remove();
			--count;

			if (last == &(Node::NIL))
			{
				head = &(Node::NIL);
			}
		}
		return value;
	}

	// Return reference to Monstera using an integer
	Monstera& operator[](int a)
	{
		int idx = 0;
		for (auto it = getIterator(); it != it.end(); ++it)
		{
			if (idx == a)
			{
				return *it.getCurrent()->getValue();
			}
			++idx;
		}

		throw std::out_of_range("Out of range");
	}

	// Insert a new node at anywhere of the list that's not head or tail
	void insert(int idx, Monstera* value)
	{
		int index = 0;
		Node* newNode = new Node(*value);
		if (idx == 0 || idx >= count)
		{
			cout << "You cannot insert at the head or tail" << endl;
		}
		else
		{
			for (auto it = getIterator(); it != it.end(); ++it)
			{
				if (index == idx)
				{
					it.getCurrent()->prepend(newNode);
				}
				++index;
			}
		}
	}

	// Remove a node from anywhere in the list
	void remove(int x, int y)
	{
		for (auto it = getIterator(); it != it.end(); ++it)
		{
			cout << it.getCurrent()->getValue()->getName() << endl;
			if (it.getCurrent()->getValue()->getXCoordinate() == x && it.getCurrent()->getValue()->getYCoordinate() == y)
			{
				it.getCurrent()->remove();
				if (head == &(Node::NIL))
				{
					last = &(Node::NIL);
				}

				if (last == &(Node::NIL))
				{
					head = &(Node::NIL);
				}

				return;
			}
		}
		cout << "Cannot find Monstera at this coordinate" << endl;
	}

	Node& getHead()
	{
		return *head;
	}

	// Return an iterator object
	Iterator getIterator() const
	{
		return Iterator(head);
	}
};

