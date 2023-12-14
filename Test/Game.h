#pragma once
#include <iostream>
#include "Gacha.h"
#include "List.h"
#include "Monstera.h"
#include "AquaMonstera.h"
#include "Player.h"
#include "Map.h"
#include "Message.h"
#include "Objective.h"
using namespace std;

// This class follows the singleton design pattern meaning only one of this class' instance can exist at a time
class Game
{
private:
	static Game* instance;
	bool gameRunning;
	Player* player;
	Map* map;
	Shop* shop;
	Objective* objective;
	List* monsteras;
	int normalMonstera;
	int epicMonstera;
	int legendaryMonstera;
	bool gameSaved;
	Game();

public:
	// Static method to get the single instance of Game
	static Game* getInstance();

	// Start game and end game
	void StartGame();
	void EndGame();

	// Getter and setter for game running state
	bool getGameRunning();
	void setGameRunning(bool state);

	// Battle scenario function
	void Battle(int x, int y);

	// Add enemies to the map
	void AddEnemiesToMap();

	// Save and load game from text file
	void SaveGame(const string& fileName);
	void LoadGame(const string& fileName);

	// Destructor
	~Game();
};
