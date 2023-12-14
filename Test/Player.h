#pragma once
#include <iostream>
#include "Monstera.h"
#include "Inventory.h"
#include "Iterator.h"
using namespace std;

class Player
{
private:
	string fName;
	int fCoins;
	int fLives;
	int x;
	int y;
	Inventory* fHead; 
	Inventory* fTail; 

public:
	// Default constructor
	Player();

	// Getter and setter for the player's name
	string getName();
	void setName(string aName);

	// Getter and setter for the player's coins
	int getCoins();
	void setCoins(int aCoins);

	// Getter and setter for the player's lives
	int getLives();
	void setLives(int aLives);

	// Getter and setter for the player's coordinates
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);

	// Function to move the player to new coordinates
	void Move(int x, int y);

	// Function to add a Monstera to the player's inventory
	void AddMonstera(Monstera* aMonstera);

	// Function to remove a Monstera from the player's inventory by name
	void RemoveMonstera(const int idx);

	// Function to check if the player has a Monstera with a given name
	bool HasMonstera(string aName);

	// Getter for the player's inventory
	Inventory& getInventory() const;

	// Getter for a specific Monstera at a given index in the inventory
	Monstera& getMonstera(int idx);

	// Getter for a specific Monstera by name in the inventory
	Monstera& getMonstera(string aName);

	// Function to view all Monsteras in the player's inventory
	void ViewMonsteras();

	// Function to view information about the player
	void ViewPlayerInfo();

	// Function to get an iterator for the player's inventory
	Iterator getIterator();

	// Overloaded extraction operator to read player data from input stream
	friend std::istream& operator>>(std::istream& in, Player& player);

	// Function to serialise player data to an output stream
	void serialise(std::ostream& out) const;

	// Function to deserialise player data from an input stream
	void deserialise(std::istream& in);

	// Destructor
	~Player();
};