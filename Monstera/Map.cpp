#include "Map.h"
#include <iomanip>

// Parameterised constructor
Map::Map(int aRows, int aCols) : rows(aRows), cols(aCols) {
    // Allocate memory for the 2D array
    map = new string * [rows];
    for (int i = 0; i < rows; i++) {
        map[i] = new string[cols];
    }

    // Initialize the map with 0
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            map[i][j] = "0";
        }
    }
    finalBoss = nullptr;
}

// Draw Map
void Map::DrawMap() {
    int count = 41;
    string separator(count, '=');
    
    cout << "Legend:" << endl;
    cout << "[P] - Player" << endl;
    cout << "[S] - Shop" << endl;
    cout << "[N] - Normal Monstera" << endl;
    cout << "[E] - Epic Monstera" << endl;
    cout << "[L] - Legendary Monstera" << endl;
    cout << "[F] - Final Boss" << endl;
    cout << separator << endl;
    for (int i = 0; i < rows; i++) {
        cout << "{";
        for (int j = 0; j < cols; j++) {
            // Check if player position is here, then draw [P] on map
            if (IsPlayerPosition(i, j)) {
                cout << "[P]";
            }
            // If not, change the initialised string 0 to X
            else if (map[i][j] == "0") {
                map[i][j] = " X ";
                cout << setw(2) << map[i][j];
            }
            // Otherwise, print out the content of that position, can be [N], [S], etc
            else
            {
                cout << setw(1) << map[i][j];
            }
            // Add horizontal spaces between the items in the map
            if (j < cols - 1) {
                cout << " ";
            }
        }
        cout << "}";
        cout << endl;
    }
    cout << separator << endl;
}

// Check if a position has player
bool Map::IsPlayerPosition(int x, int y) {
    if (player->getX() == x && player->getY() == y) {
        return true;
    }
    return false;
}

// Check if the player's position is within map coundary
bool Map::IsPlayerPositionValid(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

// Add player onto the map
void Map::AddPlayer(Player& aPlayer) {
    this->player = &aPlayer;
}

// Add Final Boss onto the map
void Map::AddFinalBoss(Monstera* enemy)
{
    this->finalBoss = enemy;
    int x = 9;
    int y = 9;
    map[x][y] = "[F]";
}

// Get Final Boss
Monstera* Map::getFinalBoss()
{
    return this->finalBoss;
}

// Get Monstera by coordinate
Monstera* Map::getEnemyByCoordinate(int x, int y)
{
    auto it = monsteras.getIterator();
    while (it != it.end())
    {
        if (it.getCurrent()->getValue()->getXCoordinate() == x && it.getCurrent()->getValue()->getYCoordinate() == y)
        {
            return it.getCurrent()->getValue();
        }
        it++;
    }
}

 //Add enemy onto the map and the list
void Map::AddEnemy(Monstera* enemy) {
    monsteras.push_back(*enemy);

    int x, y;
    do {
        x = rand() % rows;
        y = rand() % cols;
    } while ((x < 2 && y < 2) || (x == 5 && y && 5) || getEnemyByCoordinate(x, y) != nullptr);

    if (enemy->RarityToString() == "Normal")
    {
        map[x][y] = "[N]";
    }
    else if (enemy->RarityToString() == "Epic")
    {
        map[x][y] = "[E]";
    }
    else
    {
        map[x][y] = "[L]";
    }

    enemy->setCoordinate(x, y);
}

// Remove enemy from the map and the list
void Map::RemoveEnemy(int x, int y)
{
    map[x][y] = " X ";
}

// Add shop onto the map
void Map::AddShop(Shop* shop)
{
    this->shop = shop;
    int x, y;
    x = 5;
    y = 5;

    map[x][y] = "[S]";
}

// Return the list of Monsteras on the map
List& Map::getMonsteras()
{
    return monsteras;
}

// Return the string shown on map using coordinates
string Map::getMap(int x, int y)
{
    return map[x][y];
}

// Serialization function
void Map::serialise(std::ostream& out) const
{
    // Save rows and cols
    out << rows << " " << cols << "\n";

    // Save player position
    out << player->getX() << " " << player->getY() << "\n";

}

// Deserialization function
void Map::deserialise(std::istream& in)
{
    // Read rows and cols
    in >> rows >> cols;

    // Read player position
    int playerX, playerY;
    in >> playerX >> playerY;
    player->setX(playerX);
    player->setY(playerY);
}

// Destructor 
Map::~Map() {
    // Delete the map array
    if (map != nullptr)
    {
        for (int i = 0; i < rows; ++i)
        {
            delete[] map[i];
        }
        delete[] map;
        map = nullptr;
    }

    // Delete the finalBoss object
    if (finalBoss != nullptr)
    {
        delete finalBoss;
        finalBoss = nullptr;
    }

    // Delete the shop object
    if (shop != nullptr)
    {
        delete shop;
        shop = nullptr;
    }
}

