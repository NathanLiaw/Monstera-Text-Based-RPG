#include "Game.h"
#include <iostream>
#include <fstream>
#include "FlameMonstera.h"
#include "AquaMonstera.h"
#include "TerraMonstera.h"
#include "BTree.h"
#include <iomanip>
using namespace std;

// Constructor
Game::Game()
{
    gameRunning = true;
    gameSaved = false;
    player = new Player();
    map = new Map(10, 10);
    map->AddPlayer(*player);
    //map->DrawMap();

    // Add objectives into the game
    objective = new Objective();
    objective->AddObjective("Objective 1: Go to a shop (S) on the map and open a Normal gacha", 15);
    objective->AddObjective("Objective 2: Defeat a Normal Monstera (N) on the map", 10);
    objective->AddObjective("Objective 3: Upgrade your Monstera once", 10);
    objective->AddObjective("Objective 4: Have at least 1 Epic Monstera", 30);
    objective->AddObjective("Objective 5: Defeat an Epic Monstera (E) on the map", 30);
    objective->AddObjective("Objective 6: Have 1 of your Epic Monstera reach Level 5", 30);
    objective->AddObjective("Objective 7: Defeat a Legendary Monstera (L) on the map", 50);
    objective->AddObjective("Final Objective: Defeat the Final Boss", 1000);

    // Creating All Monsteras for this game
    FlameMonstera* Spark = new FlameMonstera("Spark", 100.0, 30.0, Rarity::Normal, 7, 10.0, 14.0, 2.0, 4.0, 1, 2.0);
    FlameMonstera* Blaze = new FlameMonstera("Blaze", 100.0, 35.0, Rarity::Normal, 7, 9.0, 15.0, 3.0, 5.0, 1, 2.0);
    FlameMonstera* Pyro = new FlameMonstera("Pyro", 100.0, 30.0, Rarity::Normal, 7, 11.0, 14.0, 3.0, 5.0, 1, 2.0);
    FlameMonstera* Ember = new FlameMonstera("Ember", 150.0, 60.0, Rarity::Epic, 8, 13.0, 17.0, 5.0, 7.0, 1, 3.0);
    FlameMonstera* Inferno = new FlameMonstera("Inferno", 170.0, 100.0, Rarity::Legendary, 9, 15.0, 20.0, 4.0, 10.0, 1, 5.0);

    AquaMonstera* Merlion = new AquaMonstera("Merlion", 130.0, 35.0, Rarity::Normal, 7, 6.0, 11.0, 3.0, 6.0, 1, 2.0);
    AquaMonstera* Vortex = new AquaMonstera("Vortex", 135.0, 35.0, Rarity::Normal, 7, 7.0, 10.0, 4.0, 7.0, 1, 2.0);
    AquaMonstera* Tidal = new AquaMonstera("Tidal", 155.0, 50.0, Rarity::Epic, 8, 10.0, 15.0, 5.0, 7.5, 1, 3.0);
    AquaMonstera* Poseidon = new AquaMonstera("Poseidon", 160.0, 80.0, Rarity::Epic, 8, 10.0, 15.0, 6.0, 8.5, 1, 3.0);
    AquaMonstera* DeepBlue = new AquaMonstera("DeepBlue", 180.0, 100.0, Rarity::Legendary, 9, 12.0, 16.0, 6.5, 10.5, 1, 5.0);

    TerraMonstera* Guardian = new TerraMonstera("Guardian", 110.0, 35.0, Rarity::Normal, 7, 6.5, 11.5, 4.0, 10.0, 1, 2.0);
    TerraMonstera* StoneGolem = new TerraMonstera("StoneGolem", 115.0, 35.0, Rarity::Normal, 7, 5.5, 10.5, 4.5, 10.5, 1, 2.0);
    TerraMonstera* Atlas = new TerraMonstera("Atlas", 125.5, 70.0, Rarity::Epic, 8, 10.5, 14.5, 6.5, 12.5, 1, 3.0);
    TerraMonstera* WoodDragon = new TerraMonstera("WoodDragon", 145.0, 70.0, Rarity::Legendary, 9, 11.5, 15.0, 7.0, 14.0, 1, 5.0);
    TerraMonstera* Gaia = new TerraMonstera("Gaia", 145.0, 100.0, Rarity::Legendary, 9, 8.5, 15.0, 8.5, 15.5, 1, 5.0);

    // Final Boss
    FlameMonstera* StormWeaver = new FlameMonstera("StormWeaver", 200.0, 50.0, Rarity::Legendary, 9, 16.0, 22.0, 10.0, 15.0, 10, 5.0);

    monsteras = new List();

    // Adding Flame Monsteras to the list
    monsteras->push_back(*Spark);
    monsteras->push_back(*Blaze);
    monsteras->push_back(*Pyro);
    monsteras->push_back(*Ember);
    monsteras->push_back(*Inferno);

    // Adding Aqua Monsteras to the list
    monsteras->push_back(*Merlion);
    monsteras->push_back(*Vortex);
    monsteras->push_back(*Tidal);
    monsteras->push_back(*Poseidon);
    monsteras->push_back(*DeepBlue);

    // Adding Terra Monsteras to the list
    monsteras->push_back(*Guardian);
    monsteras->push_back(*StoneGolem);
    monsteras->push_back(*Atlas);
    monsteras->push_back(*WoodDragon);
    monsteras->push_back(*Gaia);

    // Add the enemies onto the map
    this->AddEnemiesToMap();

    // Initialise the shop and pass the monsteras list into it for the Gachas
    shop = new Shop(monsteras, objective);
    map->AddShop(shop);
    map->AddFinalBoss(StormWeaver); // Add the final boss into the game

    // Set precision to 1 decimal place
    std::cout << std::fixed << std::setprecision(1);

    // Singleton instance for Game class
    instance = this;
}

// Battle scenario function
void Game::Battle(int x, int y)
{
    int enemyX = 0;
    int enemyY = 0;
    // Get enemy from map using coordinate
    Monstera* enemy;
    if (x == 9 && y == 9)
    {
        enemy = map->getFinalBoss()->Clone();
    }
    else
    {
        try {
            enemy = (map->getEnemyByCoordinate(x, y))->Clone();
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Exception caught: " << e.what() << std::endl;
            
            // This is a failsafe but assigning enemy to the first enemy in the list in case it couldn't clone 
            enemy = &monsteras->operator[](0);
        }
    }
    
    enemyX = enemy->getXCoordinate();
    enemyY = enemy->getYCoordinate();
    // Initialising local variables
    Monstera* playerMonstera = nullptr;
    int monsteraIndex = 0;
    int userInput = 0;
    int count = 41;
    string separator(count, '+');
    BTree* conditionTree = enemy->CreateConditionTree();

    // Displaying enemy info
    std::cout << "You are entering a battle with " << enemy->getName() << endl;
    enemy->DisplayDetails();

    // Select the Monstera to battle
    std::cout << "Select a Monstera for battle: " << endl;
    player->ViewMonsteras();
    cin >> monsteraIndex;
    playerMonstera = player->getMonstera(monsteraIndex).Clone();

    // Display player's and enemy's Monstera information
    std::cout << separator << endl;
    std::cout << "Your Monstera: " << endl;
    playerMonstera->DisplayDetails();
    std::cout << endl;

    std::cout << "Enemy Monstera: " << endl;
    enemy->DisplayDetails();
    std::cout << separator << endl;

    // Actions for battle scenario
    while (playerMonstera->IsAlive() && enemy->IsAlive())
    {
        std::cout << "Name: " << playerMonstera->getName() << endl;
        std::cout << "HP: " << playerMonstera->getHp() << endl;
        std::cout << "MP: " << playerMonstera->getMp() << endl;
        std::cout << "Stamina: " << playerMonstera->getStamina() << endl;
        std::cout << endl; 

        std::cout << "Name: " << enemy->getName() << endl;
        std::cout << "HP: " << enemy->getHp() << endl;
        std::cout << "MP: " << enemy->getMp() << endl;
        std::cout << "Stamina: " << enemy->getStamina() << endl;
        std::cout << endl;

        playerMonstera->BattleOptions(enemy);
        std::cout << endl;

        std::cout << "Enemy's Actions: ";
        enemy->ExecuteBehaviorTree(conditionTree, playerMonstera);
        
        // End turn and gain +1 stamina got everyone
        playerMonstera->Rest();
        enemy->Rest();

        std::cout << endl;
    }

    // If enemy is not alive, player wins
    if (!enemy->IsAlive())
    {
        std::cout << "Player wins" << endl;
        std::cout << objective->ClearObjective(player, 2) << endl;
        if (enemy->getName() == "StormWeaver")
        {
            objective->ClearObjective(player, 8);
            std::cout << "Congratulation! You have completed the game" << endl;
            this->EndGame();
        }
        else if (enemy->RarityToString() == "Epic")
        {
            player->setCoins(player->getCoins() + 20);
            playerMonstera->LevelUp(60);
            std::cout << objective->ClearObjective(player, 5) << endl;
        }
        else if (enemy->RarityToString() == "Legendary")
        {
            player->setCoins(player->getCoins() + 30);
            playerMonstera->LevelUp(90);
            std::cout << objective->ClearObjective(player, 7) << endl;
        }
        else
        {
            player->setCoins(player->getCoins() + 10);
            playerMonstera->LevelUp(30);
        }
        map->RemoveEnemy(enemyX, enemyY);
    }
    else
    {
        int lives = player->getLives();
        player->setLives(player->getLives() - 1);
        std::cout << "You lost" << endl;
        std::cout << "Lives: " << lives << "->" << player->getLives() << endl;
        if (player->getLives() <= 0)
        {
            this->EndGame();
        }
    }
}

// Function to add enemies to the map, ensure that there are at least 10 normal,
// 5 epic, and 4 legendary Monsteras on the map
void Game::AddEnemiesToMap()
{
    while (normalMonstera < 10 || epicMonstera < 5 || legendaryMonstera < 4)
    {
        int random = rand() % 15;
        Monstera* temp = &monsteras->operator[](random);
        if (temp->RarityToString() == "Normal" && normalMonstera < 10)
        {
            normalMonstera++;
        }
        else if (temp->RarityToString() == "Epic" && epicMonstera < 5)
        {
            epicMonstera++;
        }
        else if (temp->RarityToString() == "Legendary" && legendaryMonstera < 4)
        {
            legendaryMonstera++;
        }
        else
        {
            continue;
        }

        // If the coordinate already has a Monstera, skip to next iteration
        if (map->getEnemyByCoordinate(temp->getXCoordinate(), temp->getYCoordinate()))
        {
            continue;
        }
        else
        {
            // Clone the Monstera and store it into map
            map->AddEnemy(temp->Clone());
        }
    }
}

// Return bool if game is still running
bool Game::getGameRunning()
{
    return gameRunning;
}

// Setter for gameRunning
void Game::setGameRunning(bool state)
{
    gameRunning = state;
}

// Initialize the static instance pointer to nullptr
Game* Game::instance = nullptr;

// Get the instance of this game object and do lazy initialization
Game* Game::getInstance() {
    if (!instance) {
        instance = new Game();
    }
    return instance;
}

// Start main flow of the game
void Game::StartGame()
{
    int count = 41;
    string separator(count, '*');
    string userInput = "";
    // Adding messages built using singly linked list
    Message* msg = new Message("Waking up in a meadow bathed in the ethereal glow of a dual-moon night, You found yourself disoriented and surrounded by an otherworldly silence.\n");
    msg->addMessage("The air shimmered with magic, and the grass beneath you seemed to hum with a mystic energy.\n");
    msg->addMessage("Struggling to recall how you arrived, your memory danced like elusive shadows on the edge of your consciousness.\n");
    msg->addMessage("'Argh...my head hurts...'\n");
    msg->addMessage("All of a sudden, you notice a subtle movement in the tall grass nearby. What would you do?\n1. Approach Cautiously\n2. Stay");
    
    if (gameSaved != true)
    {
        string name = "";
        std::cout << "What is your name? :" << endl;
        cin >> name;
        player->setName(name);

        Message* temp = msg;
        int idx = 0;

        // Print out messages 
        while (temp != (Message*)0)
        {
            std::cout << temp->getMessage() << endl;
            if (idx == 4) {
                string action = "";
                cin >> action;
                if (action == "1")
                {
                    FlameMonstera* Spark = new FlameMonstera("Spark", 100.0, 30.0, Rarity::Normal, 7, 10.0, 14.0, 2.0, 4.0, 1, 2.0);
                    std::cout <<
                        "Slowly and cautiously, you advanced, and to your surprise, it was a baby Spark."
                        "It appears to have taken a liking to you. It is now yours to care." << endl;
                    player->AddMonstera(Spark);
                }
                else
                {
                    std::cout << "The rustling in the grass faded away, only to be replaced by the sudden appearance of someone behind you." << endl;

                    std::cout << "Moments later, the person who appeared took you to the nearby town called Montero." << endl;
                    break;
                }
            }
            else {
                std::cout << "Enter any key to continue..." << endl;
                cin >> userInput;
                std::cout << endl;
            }
            temp = &temp->getNext();
            ++idx;
        }
    }
    else
    {
        std::cout << "Welcome back " << player->getName() << endl;
    }

    // Main flow of the game
    while (userInput != "Exit" && getGameRunning() == true)
    {
        // Print current objective
        std::cout << objective->getObjective() << endl;
        std::cout << separator << endl;

        // Draw map
        map->DrawMap();

        std::cout << "[1] Enter a, w, s, d to move around the map" << endl;
        std::cout << "[2] View player details" << endl;
        std::cout << "[3] View inventory" << endl;
        std::cout << "[4] Save game" << endl;
        std::cout << "[5] Exit game" << endl;
        cin >> userInput;

        if (userInput == "2")
        {
            player->ViewPlayerInfo();
        }
        else if (userInput == "3")
        {
            player->ViewMonsteras();
        }
        else if (userInput == "4")
        {
            gameSaved = true;
            this->SaveGame("save_data.txt");
        }
        else if (userInput == "5")
        {
            this->EndGame();
            break;
        }

        // Determine movement based on user input
        int deltaX = 0;
        int deltaY = 0;

        if (userInput == "W" || userInput == "w") {
            deltaX = -1; // Move up
        }
        else if (userInput == "S" || userInput == "s") {
            deltaX = 1;  // Move down
        }
        else if (userInput == "A" || userInput == "a") {
            deltaY = -1; // Move left
        }
        else if (userInput == "D" || userInput == "d") {
            deltaY = 1;  // Move right
        }

        // Attempt to move the player
        int newX = player->getX() + deltaX;
        int newY = player->getY() + deltaY;

        if (map->IsPlayerPositionValid(newX, newY)) {
            if (map->getMap(newX, newY) == " X ")
            {
                // Only move the player if the new position is valid
                player->Move(deltaX, deltaY);
            }
            else if (map->getMap(newX, newY) == "[S]")
            {
                shop->OpenShop(player);
            }
            else if (map->getMap(newX, newY) == "[F]")
            {
                auto it = player->getIterator();
                while (it != it.end())
                {
                    Monstera* temp = &it.getCurrent()->getMonstera();
                    if (temp->getLevel() >= 5 && temp->RarityToString() == "Epic")
                    {
                        Battle(newX, newY);
                        break;
                    }
                    it++;
                }
            }
            else if (map->getMap(newX, newY) == "[N]")
            {
                if (player->getInventory().size() > 0)
                {
                    Battle(newX, newY);
                }
                else
                {
                    std::cout << "You don't have any Monstera yet. Go to the shop to get one." << endl;
                }
            }else if (map->getMap(newX, newY) == "[E]")
            {
                if (player->getInventory().size() > 0)
                {
                    Battle(newX, newY);
                }
                else
                {
                    std::cout << "You don't have any Monstera yet. Go to the shop to get one." << endl;
                }
            }else if (map->getMap(newX, newY) == "[L]")
            {
                if (player->getInventory().size() > 0)
                {
                    Battle(newX, newY);
                }
                else
                {
                    std::cout << "You don't have any Monstera yet. Go to the shop to get one." << endl;
                }
            }
        }
        else {
            // Player attempt to exit map
            std::cout << "You can't leave" << endl;
        }

        // Check objectives
        int epicOwned = 0;
        int level5 = 0;
        auto it = player->getIterator();
        if (!player->getInventory().isEmpty())
        {
            while (it != it.end())
            {
                Monstera* temp = &it.getCurrent()->getMonstera();
                    if (temp->RarityToString() == "Epic")
                    {
                        epicOwned++;
                    }
                    if (temp->RarityToString() == "Epic" && temp->getLevel() >= 5) 
                    {
                        level5++;
                    }
                it++;
            }
        }
        if (epicOwned > 0)
        {
            std::cout << objective->ClearObjective(player, 4) << endl;
        }
        if (level5 > 0)
        {
            std::cout << objective->ClearObjective(player, 6) << endl;
        }    
    }
}

// Function to save game data to a text file
void Game::SaveGame(const string& fileName)
{
    // Open the file for writing
    ofstream outFile(fileName);

    if (outFile.is_open()) {
        int monsteraType[15] = { 0 };
        // Save player data
        player->serialise(outFile);

        // Save map data (assuming Map has a serialize function)
        map->serialise(outFile);

        // Save player's inventory data
        int size = player->getInventory().size();
        int count = 0;
        auto it = player->getIterator();
        for (it = it.begin(); it != it.end(); it++)
        {
            if (it.getCurrent()->getMonstera().ElementToString() == "Aqua")
            {
                monsteraType[count] = 1;
            }
            else if (it.getCurrent()->getMonstera().ElementToString() == "Flame")
            {
                monsteraType[count] = 2;
            }
            else
            {
                monsteraType[count] = 3;
            }
            count++;
        }

        // Save the inventory size
        outFile << size << "\n";

        // Serialise the Monstera's data
        int idx = 0;
        auto iter = player->getIterator();
        for (iter = iter.begin(); iter != iter.end(); iter++)
        {
            outFile << monsteraType[idx] << " ";
            outFile << "\n";
            iter.getCurrent()->getMonstera().serialise(outFile);
            idx++;
        }

        // Close the file
        outFile.close();

        std::cout << "Game saved successfully to " << fileName << endl;
    }
    else {
        cerr << "Unable to open file for writing: " << fileName << endl;
    }
}

// Function to load game data from a text file
void Game::LoadGame(const std::string& fileName) {
    // Open the file for reading
    std::ifstream inFile(fileName);

    if (inFile.is_open()) {
        // Set gameSaved is true
        gameSaved = true;

        // Load player data
        player->deserialise(inFile);
        map->AddPlayer(*player);

        // Load map data 
        map->deserialise(inFile);

        // Load player's inventory data
        int count;
        inFile >> count;
        int monsteraType;
        for (int i = 0; i < count; ++i) {
            inFile >> monsteraType;

            // Declare variables outside the switch statement
            Monstera* tempMonstera = nullptr;

            // Create the appropriate Monstera based on the loaded type
            switch (monsteraType) {
            case 1:
                // Aqua Monstera
                tempMonstera = new AquaMonstera();
                break;
            case 2:
                // Flame Monstera
                tempMonstera = new FlameMonstera();
                break;
            case 3:
                // Terra Monstera
                tempMonstera = new TerraMonstera();
                break;
            default:
                continue;
            }

            // Check if tempMonstera is not null before deserializing
            if (tempMonstera != nullptr) {
                tempMonstera->deserialise(inFile);
                player->AddMonstera(tempMonstera);
            }
        }

        // Close the file
        inFile.close();

        std::cout << "Game loaded successfully from " << fileName << std::endl;
    }
    else {
        std::cerr << "Unable to open file for reading: " << fileName << std::endl;
    }
}

// End the game
void Game::EndGame()
{
    cout << "Game Over" << endl;
    gameRunning = false;
}

// Destructor
Game::~Game()
{
    // Delete the player
    if (player != nullptr) {
        delete player;
        player = nullptr;
    }

    // Delete the map
    if (map != nullptr) {
        delete map;
        map = nullptr;
    }

    // Delete the shop
    if (shop != nullptr) {
        delete shop;
        shop = nullptr;
    }

    // Delete the objective
    if (objective != nullptr) {
        delete objective;
        objective = nullptr;
    }

    // Delete the list of monsters
    if (monsteras != nullptr) {
        delete monsteras;
        monsteras = nullptr;
    }

    instance = nullptr;
}