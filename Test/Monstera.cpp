#include "Monstera.h"
#include <time.h>
#include <iomanip>

// Default constructor
Monstera::Monstera()
{
    fName = "Pikamon";
    fMaxHp = 100;
    fHp = fMaxHp;
    fMaxMp = 100;
    fMp = 0;
    fElement = Element::Aqua;
    fRarity = Rarity::Normal;
    fStamina = 7;
    fMinDamage = 10;
    fMaxDamage = 15;
    fMinDefense = 2;
    fMaxDefense = 4;
    fDamageBlocked = 0;
    fDodge = false;
    fLevel = 1;
    fExp = 0;
    x = 3;
    y = 3;
}

// Parameterized Constructor
Monstera::Monstera(string aName, double aMaxHp, double aMaxMp,
    Rarity aRarity, int aStamina, double aMinDamage, double aMaxDamage,
    double aMinDefense, double aMaxDefense, int aLevel)
    : fName(aName), fMaxHp(aMaxHp), fMaxMp(aMaxMp), fRarity(aRarity),
    fStamina(aStamina), fMinDamage(aMinDamage), fMaxDamage(aMaxDamage), fMinDefense(aMinDefense),
    fMaxDefense(aMaxDefense), fLevel(aLevel) {

    fElement = Element::Aqua;
    fDodge = false;
    fHp = fMaxHp;
    fMp = fMaxMp;
    fDamageBlocked = 0;
    fLevel = 1;
    fExp = 0;
    x = 3;
    y = 3;
}

// Copy constructor
Monstera::Monstera(const Monstera& other)
    : fName(other.fName),
    fHp(other.fHp),
    fMaxHp(other.fMaxHp),
    fMp(other.fMp),
    fMaxMp(other.fMaxMp),
    fElement(other.fElement),
    fRarity(other.fRarity),
    fStamina(other.fStamina),
    fMinDamage(other.fMinDamage),
    fMaxDamage(other.fMaxDamage),
    fMinDefense(other.fMinDefense),
    fMaxDefense(other.fMaxDefense),
    fDamageBlocked(other.fDamageBlocked),
    fLevel(other.fLevel),
    fExp(other.fExp),
    fDodge(other.fDodge),
    x(other.x),
    y(other.y) {
}

// Assignment operator
Monstera& Monstera::operator=(const Monstera& other) {
    if (this != &other) {
        fName = other.fName;
        fHp = other.fHp;
        fMaxHp = other.fMaxHp;
        fMp = other.fMp;
        fMaxMp = other.fMaxMp;
        fElement = other.fElement;
        fRarity = other.fRarity;
        fStamina = other.fStamina;
        fMinDamage = other.fMinDamage;
        fMaxDamage = other.fMaxDamage;
        fMinDefense = other.fMinDefense;
        fMaxDefense = other.fMaxDefense;
        fDamageBlocked = other.fDamageBlocked;
        fLevel = other.fLevel;
        fExp = other.fExp;
        fDodge = other.fDodge;
        x = other.x;
        y = other.y;

    }
    return *this;
}

// Getter and setter for fName
string Monstera::getName() const {
    return fName;
}

void Monstera::setName(const string& aName) {
    fName = aName;
}

// Getter and setter for fHp
double Monstera::getHp() const {
    return fHp;
}

void Monstera::setHp(double aHp) {
    fHp = aHp;
}

// Getter and setter for fMaxHp
double Monstera::getMaxHp() const {
    return fMaxHp;
}

void Monstera::setMaxHp(double aMaxHp) {
    fMaxHp = aMaxHp;
}

// Getter and setter for fMp
double Monstera::getMp() const {
    return fMp;
}

void Monstera::setMp(double aMp) {
    fMp = aMp;
}

// Getter and setter for fMaxMp
double Monstera::getMaxMp() const {
    return fMaxMp;
}

void Monstera::setMaxMp(double aMaxMp) {
    fMaxMp = aMaxMp;
}

// Getter and setter for fElement
Element Monstera::getElement() const {
    return fElement;
}

void Monstera::setElement(const Element& aElement) {
    fElement = aElement;
}

// Getter and setter for fRarity
Rarity Monstera::getRarity() const {
    return fRarity;
}

void Monstera::setRarity(Rarity aRarity) {
    fRarity = aRarity;
}

// Getter and setter for fStamina
int Monstera::getStamina() const {
    return fStamina;
}

void Monstera::setStamina(int aStamina) {
    fStamina = aStamina;
}

// Getter and setter for fMinDamage
double Monstera::getMinDamage() const {
    return fMinDamage;
}

void Monstera::setMinDamage(double aMinDamage) {
    fMinDamage = aMinDamage;
}

// Getter and setter for fMaxDamage
double Monstera::getMaxDamage() const {
    return fMaxDamage;
}

void Monstera::setMaxDamage(double aMaxDamage) {
    fMaxDamage = aMaxDamage;
}

// Getter and setter for fMinDefense
double Monstera::getMinDefense() const {
    return fMinDefense;
}

void Monstera::setMinDefense(double aMinDefense) {
    fMinDefense = aMinDefense;
}

// Getter and setter for fMaxDefense
double Monstera::getMaxDefense() const {
    return fMaxDefense;
}

void Monstera::setMaxDefense(double aMaxDefense) {
    fMaxDefense = aMaxDefense;
}

// Getter and setter for fDamageBlocked
double Monstera::getDamagedBlocked() const {
    return fDamageBlocked;
}

void Monstera::setDamageBlocked(double aDamage) {
    fDamageBlocked = aDamage;
}

// Getter and setter for fLevel
int Monstera::getLevel() const {
    return fLevel;
}

void Monstera::setLevel(int aLevel) {
    fLevel = aLevel;
}

// Getter and setter for fExp
int Monstera::getExp() const {
    return fExp;
}

void Monstera::setExp(int aExp) {
    fExp = aExp;
}

// Getter and setter for fDodge
bool Monstera::getDodge() const
{
    return fDodge;
}

void Monstera::setDodge(bool aState)
{
    fDodge = aState;
}

// Getter and setter for coordinate
int Monstera::getXCoordinate() const
{
    return x;
}

int Monstera::getYCoordinate() const
{
    return y;
}

void Monstera::setCoordinate(int x, int y)
{
    this->x = x;
    this->y = y;
}

// Display details about this Monstera
void Monstera::DisplayDetails()
{
    cout << "Name: " << fName << endl;
    cout << "Level: " << fLevel << endl;
    cout << "Max HP: " << fMaxHp << endl;
    cout << "Max MP: " << fMaxMp << endl;
    cout << "Damage: " << fMinDamage << "-" << fMaxDamage << endl;
    cout << "Defense: " << fMinDefense << "-" << fMaxDefense << endl;
    cout << "Stamina: " << fStamina << endl;
    cout << "Element: " << this->ElementToString() << endl;
    cout << "Rarity: " << this->RarityToString() << endl;
    cout << endl;
}

// Check if entity is still alive via the hp
bool Monstera::IsAlive()
{
    if (fHp <= 0)
    {
        return false;
    }
    return true;
}

// Roll for a random value by taking in a min double and max double
double Monstera::RollValue(double aMinStat, double aMaxStat)
{
    double randomValue = aMinStat + (static_cast<double>(std::rand()) / RAND_MAX) * (aMaxStat - aMinStat);

    return floor(randomValue * 10) / 10.0;
}

// Convert and return the enum Rarity to string
string Monstera::RarityToString()
{
    if (fRarity == Rarity::Normal)
    {
        return "Normal";
    }
    else if (fRarity == Rarity::Epic)
    {
        return "Epic";
    }
    else
    {
        return "Legendary";
    }
}

// Convert and return the enum Element to string
string Monstera::ElementToString()
{
    if (fElement == Element::Flame)
    {
        return "Flame";
    }
    else if (fElement == Element::Terra)
    {
        return "Terra";
    }
    else
    {
        return "Aqua";
    }
}

// Check if exp > 100, then increase level
void Monstera::LevelUp(int exp)
{
    int oldLevel = this->getLevel();
    int oldExp = this->fExp;
    int newExp = this->fExp + exp;
    double hp = this->fHp;
    double mp = this->fMp;
    double maxHp = this->fMaxHp;
    double maxMp = this->fMaxMp;
    double maxDmg = this->fMaxDamage;
    double minDmg = this->fMinDamage;
    double maxDef = this->fMaxDefense;
    double minDef = this->fMinDefense;

    while (newExp >= 100)
    {
        this->fLevel++;
        newExp -= 100;
        this->fMaxHp += 2;
        this->fHp += 2;
        this->fMaxMp += 2;
        this->fMp += 2;
        this->fMaxDamage += 0.5;
        this->fMinDamage += 0.5;
        this->fMaxDefense += 0.5;
        this->fMinDefense += 0.5;
    }

    // When any Monstera reaches more than level 5 the gain +1 stamina but cannot exceeds 9
    if (fLevel > 4)
    {
        int newStamina = this->fStamina += fLevel - 4;
        if (newStamina > 8)
        {
            newStamina = 9;
        }
        fStamina = newStamina;
    }

    this->fExp = newExp;
    cout << "Exp: " << oldExp << "->" << fExp << " (+" << exp << "exp)" << endl;
    cout << "Lvl: " << oldLevel << "->" << fLevel << endl;
    cout << "Max HP: " << maxHp << "->" << fMaxHp << endl;
    cout << "HP: " << hp << "->" << fHp << endl;
    cout << "Max MP: " << maxMp << "->" << fMaxMp << endl;
    cout << "MP: " << mp << "->" << fMp << endl;
    cout << "Damage: " << minDmg << "-" << maxDmg << "->" << fMinDamage << "-" << fMaxDamage << endl;
    cout << "Defense: " << minDef << "-" << maxDef << "->" << fMinDefense << "-" << fMaxDefense << endl;
}

// A function that has a 30% chance to dodge an attack during battle
void Monstera::Dodge() {
    double successProbability = 0.3;
    bool dodge = (static_cast<double>(std::rand()) / RAND_MAX) <= successProbability;

    if (this->getStamina() - 1 >= 0)
    {
        if (dodge) {
            this->fMp += 3;
            this->setDodge(true);
            cout << "Dodging the next attack" << endl;
        }
        else {
            cout << "\nDodge failed..." << endl;
        }
    }
    else
    {
        cout << "Insufficient stamina. Turn wasted." << endl;
    }
}

// Block damage by setting a value to the fDamageBlocked field
void Monstera::BlockDamage()
{
    double block = this->RollValue(this->getMinDefense(), this->getMaxDefense());

    if (this->getStamina() - 2 >= 0)
    {
        this->fMp += 2;
        this->setDamageBlocked(block);
        cout << "Blocking " << block << "dmg on the next turn" << endl;
    }
    else
    {
        cout << "Insufficient stamina. Turn wasted." << endl;
    }

}

// Rest to restore 1 stamina
void Monstera::Rest()
{
    this->fStamina++;
    this->fMp += 5;
    cout << "Resting... (+1 stamina)" << endl;
}

void Monstera::serialise(std::ostream& out) const {
    // Serialize Monstera data
    out << fName << " " << fHp << " " << fMaxHp << " " << fMp << " " << fMaxMp << " "
        << static_cast<int>(fElement) << " " << static_cast<int>(fRarity) << " "
        << fStamina << " " << fMinDamage << " " << fMaxDamage << " "
        << fMinDefense << " " << fMaxDefense << " "
        << fLevel << " " << fExp << "\n";
}

void Monstera::deserialise(std::istream& in) {
    // Deserialize Monstera data
    int elementInt, rarityInt;
    in >> fName >> fHp >> fMaxHp >> fMp >> fMaxMp >> elementInt >> rarityInt
        >> fStamina >> fMinDamage >> fMaxDamage >> fMinDefense >> fMaxDefense
        >> fLevel >> fExp;

    fElement = static_cast<Element>(elementInt);
    fRarity = static_cast<Rarity>(rarityInt);
}

// Function to create the condition tree
BTree* Monstera::CreateConditionTree() {
    string highStamina = "High Stamina";
    string sufficientStamina = "Sufficient Stamina";
    string lowStamina = "Low Stamina";
    string highHp = "High Hp";
    string lowHp = "Low Hp";

    // Root condition: High Stamina
    BTree* root = new BTree(highStamina);

    // Left subtree for High Stamina
    root->attachLeft(new BTree(sufficientStamina));
    root->left().attachLeft(new BTree(highHp));
    root->left().attachRight(new BTree(lowHp));

    // Right subtree for Low Stamina
    root->attachRight(new BTree(lowStamina));
    root->right().attachLeft(new BTree(highHp));
    root->right().left().attachLeft(new BTree(lowHp));

    return root;
}

// Destructor
Monstera::~Monstera()
{

}