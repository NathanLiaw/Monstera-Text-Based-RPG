#pragma once
#include <iostream>
#include "Element.h"
#include "Rarity.h"
#include "BTree.h"
using namespace std;

class Monstera
{
private:
    string fName;
    double fHp;
    double fMaxHp;
    double fMp;
    double fMaxMp;
    Element fElement;
    Rarity fRarity;
    int fStamina;
    double fMinDamage;
    double fMaxDamage;
    double fMinDefense;
    double fMaxDefense;
    double fDamageBlocked;
    int fLevel;
    int fExp;
    bool fDodge;
    int x;
    int y;

public:
    // Default constructor
    Monstera();

    // Parameterized Constructor
    Monstera(string aName, double aMaxHp, double aMaxMp,
        Rarity aRarity, int aStamina, double aMinDamage, double aMaxDamage,
        double aMinDefense, double aMaxDefense, int aLevel);

    // Copy constructor
    Monstera(const Monstera& other);

    // Destructor
    ~Monstera();

    // Assignment operator
    Monstera& operator=(const Monstera& other);

    // Getter and setter for fName
    string getName() const;
    void setName(const string& aName);

    // Getter and setter for fHp
    double getHp() const;
    void setHp(double aHp);

    // Getter and setter for fMaxHp
    double getMaxHp() const;
    void setMaxHp(double aMaxHp);

    // Getter and setter for fMp
    double getMp() const;
    void setMp(double aMp);

    // Getter and setter for fMaxMp
    double getMaxMp() const;
    void setMaxMp(double aMaxMp);

    // Getter and setter for fElement
    Element getElement() const;
    void setElement(const Element& aElement);

    // Getter and setter for fRarity
    Rarity getRarity() const;
    void setRarity(Rarity aRarity);

    // Getter and setter for fStamina
    int getStamina() const;
    void setStamina(int aStamina);

    // Getter and setter for fMinDamage
    double getMinDamage() const;
    void setMinDamage(double aMinDamage);

    // Getter and setter for fMaxDamage
    double getMaxDamage() const;
    void setMaxDamage(double aMaxDamage);

    // Getter and setter for fMinDefense
    double getMinDefense() const;
    void setMinDefense(double aMinDefense);

    // Getter and setter for fMaxDefense
    double getMaxDefense() const;
    void setMaxDefense(double aMaxDefense);

    // Getter and setter for fDamageBlocked
    double getDamagedBlocked() const;
    void setDamageBlocked(double aDamage);

    // Getter and setter for fLevel
    int getLevel() const;
    void setLevel(int aLevel);

    // Getter and setter for fExp
    int getExp() const;
    void setExp(int aExp);

    // Getter and setter for fDodge
    bool getDodge() const;
    void setDodge(bool aState);

    // Getter and setter for x and y
    int getXCoordinate() const;
    int getYCoordinate() const;
    void setCoordinate(int x, int y);

    // Display details
    void DisplayDetails();

    // Convert the rarity to a string
    string RarityToString();

    // Convert the element to a string
    string ElementToString();

    // A function to block damage
    virtual void BlockDamage();

    // To check if this Monstera is still alive
    bool IsAlive();

    // Allow a Monstera to have a chance to dodge the next attack (Random)
    void Dodge();

    // Allow a Monstera to rest and recover stamina during battle
    void Rest();

    // Allow a Monstera to level up and get stronger
    void LevelUp(int exp);

    // Roll a random value used by Block and Attack
    double RollValue(double aMinValue, double aMaxValue);

    // Create a condition tree for AI behaviour
    BTree* CreateConditionTree();

    // Virtual Functions
    // A virtual function that allow a Monstera to take damage
    virtual void TakeDamage(double aDamage, Monstera& aTarget) = 0;

    // A virtual function that allow a Monstera to attack another Monstera
    virtual void Attack(Monstera& aTarget) = 0;

    // Display battle options and execute them
    virtual void BattleOptions(Monstera* aTarget) = 0;

    // Clone the current object, an alternative to copy constructor
    virtual Monstera* Clone() const = 0;

    // Execute the AI behaviour based on condition tree
    virtual void ExecuteBehaviorTree(BTree* root, Monstera* player) = 0;

    // Execute the action based on the execute behaviour tree function
    virtual void ExecuteAction(string action, Monstera* player) = 0;

    // Serialise and deserialise functions
    void serialise(std::ostream& out) const;
    void deserialise(std::istream& in);
};