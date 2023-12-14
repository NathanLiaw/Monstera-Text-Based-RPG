#pragma once
#include <stdexcept>
using namespace std;

// A binary tree data structure
class BTree
{
private:
	string fKey;
	BTree* fLeft;
	BTree* fRight;

	// Default constructor
	BTree() : fKey()
	{
		fKey = "";
		fLeft = &NIL;
		fRight = &NIL;
	}

public:
	static BTree NIL;

	// Parameterised constructor
	BTree(string aKey) : fKey(aKey)
	{
		fLeft = &NIL;
		fRight = &NIL;
	}

	// Destructor
	~BTree()
	{
		if (fLeft != &NIL)
		{
			delete fLeft;
		}
		if (fRight != &NIL)
		{
			delete fRight;
		}
	}

	// Check is tree is empty
	bool isEmpty() const
	{
		return this == &NIL;
	}

	// Return the value in the node
	string key() const
	{
		if (isEmpty())
			throw std::domain_error("Empty node!");

		return fKey;
	}

	// Return the left node
	BTree& left() const
	{
		if (isEmpty())
			throw std::domain_error("Empty node!");

		return *fLeft;
	}

	// Return the right node
	BTree& right() const
	{
		if (isEmpty())
			throw std::domain_error("Empty node!");

		return *fRight;
	}

	// Attach a node to the left of current node
	void attachLeft(BTree* aBTree)
	{
		if (isEmpty())
			throw std::domain_error("Empty BTree");

		if (fLeft != &NIL)
			throw std::domain_error("Non-empty sub tree");

		fLeft = aBTree;
	}

	// Attach a node to the right of current node
	void attachRight(BTree* aBTree)
	{
		if (isEmpty())
			throw std::domain_error("Empty BTree");

		if (fRight != &NIL)
			throw std::domain_error("Non-empty sub tree");

		fRight = aBTree;
	}

	// Detach a node on the left of current node
	BTree* detachLeft()
	{
		if (isEmpty())
			throw std::domain_error("Empty BTree");

		BTree& Result = *fLeft;
		fLeft = &NIL;
		return &Result;
	}

	// Detach a node on the right of current node
	BTree* detachRight()
	{
		if (isEmpty())
			throw std::domain_error("Empty BTree");

		BTree& Result = *fRight;
		fRight = &NIL;
		return &Result;
	}
};

