#pragma once
#include <iostream>
#include <string>
using namespace std;

class Player; // Forward declaration for player class

// This is an objective class that utilises a Queue data structure. 
// The class itself is a simple Queue data structure built from a Singly Linked List.
class Objective
{
private:
    // Node structure to represent each element in the queue
    struct ObjectiveData
    {
        string objective;
        int reward;

        // Node constructor
        ObjectiveData(const string& obj, int r) : objective(obj), reward(r), next(nullptr) {}

        ObjectiveData* next; 
    };

    ObjectiveData* front; 
    ObjectiveData* rear;  
    int index;        

public:
    // Default constructor
    Objective() : front(nullptr), rear(nullptr), index(1) {}

    // Function to check if the queue is empty
    bool isEmpty() const
    {
        return front == nullptr;
    }

    // Function to add an objective to the queue
    void AddObjective(const std::string& value, int aReward)
    {
        ObjectiveData* newNode = new ObjectiveData(value, aReward);

        if (isEmpty())
        {
            // If the queue is empty, set both front and rear to the new node
            front = rear = newNode;
        }
        else
        {
            // If the queue is not empty, add the new node to the rear
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Function to clear an objective from the queue based on the index
    string ClearObjective(Player* player, int idx)
    {
        if (isEmpty())
        {
            return "";
        }

        if (index == idx)
        {
            index++;
            ObjectiveData* frontObjective = front;
            int coinsReward = 0;
            coinsReward = frontObjective->reward;
            player->setCoins(player->getCoins() + frontObjective->reward);

            front = front->next;
            delete frontObjective;

            if (front == nullptr)
            {
                // If the front becomes null, the queue is now empty
                rear = nullptr;
            }

            return "Objective Completed! +" + to_string(coinsReward) + " coins";
        }

        return "";
    }

    // Function to get the description of the front objective
    string getObjective()
    {
        if (isEmpty())
        {
            cerr << "Queue is empty." << endl;
            return "";
        }

        return front->objective + " (+" + to_string(front->reward) + " coins)";
    }

    // Function to get the current index
    int getIndex()
    {
        return index;
    }

    // Destructor to delete all nodes when the queue is destroyed
    ~Objective()
    {
        while (front != nullptr)
        {
            // Delete nodes one by one until the queue is empty
            ObjectiveData* temp = front;
            front = front->next;
            delete temp;
        }
    }
};
