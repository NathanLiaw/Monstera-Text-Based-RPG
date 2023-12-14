#pragma once
#include <iostream>
#include "Gacha.h"
#include "Player.h"
#include "Objective.h"
using namespace std;

// A shop class that allows a player to interact with the shop, 
// including opening the shop, rolling gacha, and upgrading Monsteras.
class Shop
{
private:
	Gacha* fNormal;    
	Gacha* fEpic;     
	Gacha* fLegendary;
	Objective* fObjectives; 

public:
	// Constructor 
	Shop(List* monsteras, Objective* objectives);

	// Function to open the shop and allow the player to interact with it
	void OpenShop(Player* player);

	// Function to upgrade a Monstera in the player's inventory
	void Upgrade(string aName, Player* player);

	// Function to get a reference to a specific gacha based on its name
	Gacha& getGacha(string aName);

	// Destructor
	~Shop();
};
