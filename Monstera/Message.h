#pragma once
#include <iostream>

// A message class used to store string dialogues using Singly Linked List data stucture
class Message {
private:
    string fMessage;
    Message* fNext;
    Message* fTail;

public:
    // Parameterised constructor
    Message(string aMessage) : fMessage(aMessage), fNext((Message*)0), fTail(this) {}

    // Get the reference for the next node
    Message& getNext() {
        return *fNext;
    }

    // Return the string value of a node
    string getMessage() const {
        return fMessage;
    }

    // Add a string message at the tail (most right)
    void addMessage(std::string aMessage) {
        Message* newNode = new Message(aMessage);
        fTail->fNext = newNode;
        fTail = newNode;
    }

    // Destructor 
    ~Message() {
        Message* current = this;
        Message* next;
        while (current != (Message*)0) {
            next = current->fNext;
            delete current;
            current = next;
        }
    }
};
