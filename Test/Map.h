#pragma once
#include <iostream>
#include "Player.h"
#include "Shop.h"
#include "List.h"
using namespace std;

// A map class that utilise 2D array 
class Map
{
private:
	int rows;
	int cols;
	string** map;
	Player* player;
	List monsteras;
	Monstera* finalBoss;
	Shop* shop;

public:
	// Parameterised constructor
	Map(int aRows, int aCols);

	// Draw map
	void DrawMap();

	// Add player to map
	void AddPlayer(Player& player);

	// Check if current position is player's position
	bool IsPlayerPosition(int x, int y);

	// Check if player's position is within map
	bool IsPlayerPositionValid(int x, int y);
	
	// Add enemy to the map
	void AddEnemy(Monstera* enemy);

	// Remove enemy from map
	void RemoveEnemy(int x, int y);

	// Add final boss to the map
	void AddFinalBoss(Monstera* enemy);

	// Return final boss
	Monstera* getFinalBoss();

	// Return a Monstera using coordinate
	Monstera* getEnemyByCoordinate(int x, int y);

	// Add a shop to the map
	void AddShop(Shop* shop);

	// Return the list of Monsteras on the map
	List& getMonsteras();

	// Return the string shown on the map using coordinates
	string getMap(int x, int y);

	// Serialise function
	void serialise(std::ostream& out) const;

	// Deserialise function
	void deserialise(std::istream& in);

	// Destructor
	~Map();
};