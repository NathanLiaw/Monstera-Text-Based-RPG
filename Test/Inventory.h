#pragma once
#include "Monstera.h"

// Inventory class utilises a Doubly Linked List data structure to store the Monsteras of a Player
class Inventory
{
private:
    typedef Inventory Node;
    Monstera* fMonstera;
    Node* fNext;
    Node* fPrevious;
    int fCount;

public:
    static Node NIL;

    // Default constructor
    Inventory()
    {
        fNext = &NIL;
        fPrevious = &NIL;
        fCount = 0;
        fMonstera = nullptr;
    }

    // Parameterized constructor
    Inventory(Monstera& aMonstera);

    // Add monstera to end of list
    void AddMonstera(Node* newNode);

    // Returns a reference to the Monstera object stored in the current Inventory node.
    Monstera& getMonstera() const {
        return *fMonstera;
    }

    // Returns a reference to the next Inventory node in the list.
    Node& getNext() const
    {
        return *fNext;
    }

    // Returns a reference to the previous Inventory node in the list.
    Node& getPrevious() const
    {
        return *fPrevious;
    }

    // Checks if the inventory is empty.
    bool isEmpty() const { return fCount == 0; }

    // Returns a reference to the count of Monsteras in the inventory.
    int& size() { return fCount; }

    // Removes the current Inventory node from the list.
    void Remove();

    // Destructor
    ~Inventory();
    
};
