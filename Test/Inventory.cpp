#include "Inventory.h"

Inventory Inventory::NIL;

// Parameterised constructor
Inventory::Inventory(Monstera& aMonstera)
{
	fMonstera = &aMonstera;
	fNext = &NIL;
	fPrevious = &NIL;
	fCount = 1;
}

// Add a monstera to the end of the list, can only have 3 max
void Inventory::AddMonstera(Node* newNode)
{
	newNode->fPrevious = this;
	if (fNext != &NIL)
	{
		newNode->fNext = fNext;
		fNext->fPrevious = newNode;
	}
	fNext = newNode;
}

// Remove a node from the list
void Inventory::Remove()
{
	if (fNext == &NIL)
	{
		fPrevious->fNext = &NIL;
	}
	else if (fPrevious == &NIL)
	{
		fNext->fPrevious = &NIL;
	}
	else
	{
		fPrevious->fNext = fNext;
		fNext->fPrevious = fPrevious;
	}

	delete this;
}

// Destructor 
Inventory::~Inventory()
{
	if (fMonstera != nullptr) {
		delete fMonstera;
		fMonstera = nullptr; 
	}
}