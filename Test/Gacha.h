#pragma once
#include <iostream>
#include "List.h"
#include "Monstera.h"
#include "DoublyLinkedNode.h"
#include "Stack.h"
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

// A gacha class that utilise stack data structure
class Gacha
{
private:
	Stack* monsteras;
	typedef DoublyLinkedNode Node;
	List list;
	string name;
	int* limit;
	int normalFactor;
	int epicFactor;
	int legendaryFactor;
	int cost;
	Node* top;

public:
	// Default constructor
	Gacha()
	{
		name = "Normal";
		limit = new int(15);
		normalFactor = 5;
		epicFactor = 3;
		legendaryFactor = 2;
		cost = 10;
		top = &list.getHead();
		monsteras = new Stack();

		// Initialise gacha with empty list
		this->Initialize(&list, normalFactor, epicFactor, legendaryFactor);
	}

	// Parameterised constructor
	Gacha(string name, List* monsteraList, int normalFactor, int epicFactor, int legendaryFactor, int cost)
	{
		this->name = name;
		limit = new int(15);
		this->normalFactor = normalFactor;
		this->epicFactor = epicFactor;
		this->legendaryFactor = legendaryFactor;
		this->cost = cost;
		list = *monsteraList;
		monsteras = new Stack();
		top = &list.getHead();

		// Initialise gacha with list passed in parameter
		this->Initialize(monsteraList, normalFactor, epicFactor, legendaryFactor);
	}

	// Return bool if gacha is empty
	bool isEmpty() { return list.isEmpty(); }

	// Return the size of gacha
	int size() { return list.size() == 0; }

	// Return the limit of gacha
	int getLimit() const
	{
		return *limit;
	}

	// Setter for limit field
	void setLimit(int limit) const
	{
		*this->limit = limit;
	}

	// Return the cost of gacha
	int getCost() const
	{
		return cost;
	}

	// Add a Monstera into the gacha
	void AddMonstera(Monstera* value)
	{
		if (monsteras->size() <= *limit)
		{
			monsteras->Push(*value);
			if (top == &Node::NIL)
			{
				Node* newNode = new Node(*value);
				top = newNode;
			}
		}
	}

	// Helper function to convert a list to a vector
	std::vector<Monstera*> listToVector(const List& list) {
		std::vector<Monstera*> vectorList;
		auto it = list.getIterator();
		while (it != it.end()) {
			vectorList.push_back(it.getCurrent()->getValue());
			++it;
		}
		return vectorList;
	}

	// Helper function to convert a vector to a list
	List* vectorToList(const std::vector<Monstera*>& vectorList) {
		List* newList = new List();
		for (Monstera* monstera : vectorList) {
			newList->push_back(*monstera);
		}
		return newList;
	}

	// Initialize the stack with shuffled monsters and rarity-specific draw rates
	void Initialize(List* allMonstera, int normalRate, int epicRate, int legendaryRate) {
		// Explanation:
		// 1. Take the list in parameter and convert into vector
		// 2. Shuffle that vector
		// 3. Check rarity, then create multiple same objects depending on draw rate
		// 4. Store those objects in a temporary list
		// 5. Turn that temporary list into a vector
		// 6. Shuffle the vector
		// 7. Convert the vector back to list
		// 8. Push the list into the gacha stack
		
		// Convert the linked list to a vector so we can use the random shuffle function
		std::vector<Monstera*> vectorMonstera = listToVector(*allMonstera);

		// Shuffle the vector using std::shuffle
		std::random_device rd;
		std::default_random_engine rng(rd());
		std::shuffle(vectorMonstera.begin(), vectorMonstera.end(), rng);

		// Convert the shuffled vector back to a linked list
		List* shuffledMonstera = vectorToList(vectorMonstera);

		// Clear the existing stack
		while (!monsteras->isEmpty()) {
			monsteras->Pop();
		}

		// Temporary holder
		List* temp = new List();

		auto it = shuffledMonstera->getIterator();
		while(it != it.end()) {

			int drawRate;

			// Determine draw rate based on the rarity of the monster
			switch (it.getCurrent()->getValue()->getRarity()) {
			case Rarity::Legendary:
				drawRate = legendaryRate;
				break;
			case Rarity::Epic:
				drawRate = epicRate;
				break;
			default:
				drawRate = normalRate;
				break;
			}

			// Create multiple same objects depending on draw rate
			for (int i = 0; i < drawRate; i++)
			{
				temp->push_back(*it.getCurrent()->getValue());
			}
			++it;
		}
		// Convert the temporary list to a vector to shuffle it again
		std::vector<Monstera*> vectorTemp = listToVector(*temp);
		std::shuffle(vectorTemp.begin(), vectorTemp.end(), rng);

		// Convert the vector back to list
		temp = vectorToList(vectorTemp);

		// Push shuffled monsters onto the stack with rarity-specific rates
		auto iter = temp->getIterator();
		while (iter != iter.end())
		{
			monsteras->Push(*iter.getCurrent()->getValue());
			++iter;
		}
	}

	// Draw from the top of the stack
	Monstera* Roll()
	{
		if (monsteras->size() == 0) {
			cout << "Gacha is empty!" << endl;
			return nullptr;
		}

		Monstera* prize = monsteras->Pop();
		cout << "Congratulation! You got a " << prize->getName() << " with rarity " << prize->RarityToString() << endl;
		prize->DisplayDetails();
		return prize;
	}

	// Destructor
	~Gacha()
	{
		delete limit;
		delete monsteras;
	}
};
