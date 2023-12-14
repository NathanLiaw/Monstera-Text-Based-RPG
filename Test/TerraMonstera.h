#pragma once
#include "Monstera.h"
#include "Element.h"
#include "Rarity.h"
#include <iostream>
using namespace std;

class TerraMonstera : public Monstera
{
private:
	double fDamageReduction;
	bool fGaiaSap;

public:
	// Default constructor
	TerraMonstera();

	// Parameterised constructor
	TerraMonstera(string aName, double aMaxHp, double aMaxMp,
		Rarity aRarity, int aStamina, double aMinDamage, double aMaxDamage,
		double aMinDefense, double aMaxDefense, int aLevel, double aDamageReduction);

	// Clone the current object, similar to copy constructor
	virtual TerraMonstera* Clone() const override;

	// Getter and setter for field
	double getDamageReduction() const;
	void setDamageReduction(double aDamage);
	bool getGaiaSap() const;
	void setGaiaSap();

	// Override virtual functions
	void TakeDamage(double aDamage, Monstera& aTarget) override;
	void Attack(Monstera& aTarget) override;
	void BattleOptions(Monstera* aTarget) override;

	// AI behaviour
	void ExecuteBehaviorTree(BTree* root, Monstera* player) override;
	void ExecuteAction(string action, Monstera* player) override;

	// Function to serialize player data to an output stream
	void serialise(std::ostream& out) const;

	// Function to deserialize player data from an input stream
	void deserialise(std::istream& in);

	// Destructor
	~TerraMonstera();
};