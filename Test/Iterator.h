#pragma once
#include "Inventory.h"

// Iterator for the Inventory class
class Iterator
{
private:
    typedef Inventory Node;
    Node* current;

public:
    // Constructor
    Iterator(Node* start) : current(start) {}

    Iterator(Node& node) : current(&node) {}

    // Dereference operator
    Node operator*() const
    {
        return current->getMonstera();
    }

    // Return current node
    Node* getCurrent()
    {
        return current;
    }

    // Prefix increment operator
    Iterator& operator++() {
        current = &current->getNext();
        return *this;
    }

    // Postfix increment operator
    Iterator operator++(int) {
        Iterator tmp = *this;
        ++(*this);
        return tmp;
    }
    
    // Equality operator
    bool operator==(const Iterator& other)
    {
        return current == other.current;
    }

    // Inequality operator
    bool operator!=(const Iterator& other) const {
        return current != other.current;
    }

    // Begin iterator
    Iterator begin() const {
        return Iterator(current);
    }

    // End iterator
    Iterator end() {
        return Iterator(Node::NIL);
    }
};