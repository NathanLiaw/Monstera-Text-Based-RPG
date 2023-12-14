#include "Player.h"
#include "Inventory.h"

// Default constructor 
Player::Player()
{
    fName = "Dust";
    fCoins = 5000;
    fLives = 3;
    x = 0;
    y = 0;
    fHead = &Inventory::NIL; 
    fTail = &Inventory::NIL; 
}

// Getter for the player's name
string Player::getName() {
    return fName;
}

// Setter for the player's name
void Player::setName(string aName) {
    fName = aName;
}

// Getter for the player's coins
int Player::getCoins() {
    return fCoins;
}

// Setter for the player's coins
void Player::setCoins(int aCoins) {
    fCoins = aCoins;
}

// Getter for the player's lives
int Player::getLives() {
    return fLives;
}

// Setter for the player's lives
void Player::setLives(int aLives) {
    fLives = aLives;
}

// Getter for the player's X coordinate
int Player::getX() {
    return this->x;
}

// Setter for the player's X coordinate
void Player::setX(int x) {
    this->x = x;
}

// Getter for the player's Y coordinate
int Player::getY() {
    return this->y;
}

// Setter for the player's Y coordinate
void Player::setY(int y) {
    this->y = y;
}

// Allow player to move on the map
void Player::Move(int deltaX, int deltaY) {
    // Update the player's position
    this->x += deltaX;
    this->y += deltaY;
}

// Add a Monstera into the inventory
void Player::AddMonstera(Monstera* aMonstera)
{
    // Is the inventory empty, if yes add the Monstera as head and tail
    if (fHead->isEmpty()) {
        fHead = new Inventory(*aMonstera);
        fTail = fHead;
    }
    // Else, add it to the tail of the list
    else {
        Inventory* newNode = new Inventory(*aMonstera);
        fTail->AddMonstera(newNode);
        fTail = newNode;
        fHead->size()++;
    }
}

// Remove a Monstera from the inventory using name
void Player::RemoveMonstera(const int idx)
{
    int index = 0;
    auto it = getIterator();
    while (it != it.end())
    {
        if (index == idx)
        {
            it.getCurrent()->Remove();
            break;
        }
        index++;
        it++;
    }
}

// Return a reference to the inventory
Inventory& Player::getInventory() const
{
    return *fHead;
}

// Return a reference to a Monstera based on index
Monstera& Player::getMonstera(int idx)
{
    int count = 1;
    auto it = getIterator();

    while (it != it.end())
    {
        if (count == idx)
        {
            return it.getCurrent()->getMonstera();
        }
        ++it;  
        ++count;
    }

    throw std::out_of_range("Index out of range");
}

// Return a reference to a Monstera in the inventory using name
Monstera& Player::getMonstera(string aName)
{
    auto it = getIterator();
    for (it = it.begin(); it != it.end(); it++)
    {
        if (it.getCurrent()->getMonstera().getName() == aName)
        {
            return it.getCurrent()->getMonstera();
        }
    }

    throw std::out_of_range("Index out of range");
}

// View detailed information about Monstera owned by player
void Player::ViewMonsteras()
{
    auto it = getIterator();
    int idx = 1;
    if (it.begin() != Inventory::NIL) {
        while (it != it.end())
        {
            cout << "[" << idx << "] ";
            it.getCurrent()->getMonstera().DisplayDetails();
            ++it;
            ++idx;
        }
    }
    else
    {
        cout << "You don't have any Monstera yet" << endl;
    }
}

// Display info about player
void Player::ViewPlayerInfo()
{
    cout << "Name: " << fName << endl;
    cout << "Lives: " << fLives << endl;
    cout << "Coins: " << fCoins << endl;
    cout << endl;
}

// Return the iterator for inventory
Iterator Player::getIterator()
{
    return Iterator(fHead);
}

// Overloaded input operator to read data from a stream
std::istream& operator>>(std::istream& in, Player& player)
{
    in >> player.fName;
    return in;
}

// Check if player's inventory has the said Monstera using name
bool Player::HasMonstera(string aName)
{
    auto it = getIterator();
    while (it != it.end())
    {
        if (it.getCurrent()->getMonstera().getName() == aName)
        {
            return true;
        }
        ++it;
    }
    return false;
}

// Serialize the player data to a stream
void Player::serialise(std::ostream& out) const {
    out << fName << ' ' << fCoins << ' ' << fLives << ' ' << x << ' ' << y << '\n';
}

// Deserialize the player data from a stream
void Player::deserialise(std::istream& in) {
    in >> fName >> fCoins >> fLives >> x >> y;
}

// Destructor
Player::~Player()
{
    Iterator it = getIterator();
    Iterator end = it.end(); 

    while (it != end)
    {
        Inventory* toDeleteNode = it.getCurrent(); 
        ++it; 
        toDeleteNode->Remove(); 
    }

    fHead = fTail = nullptr;
}
