#pragma once
#include "Monstera.h"
#include "Element.h"
#include "Rarity.h"
#include <iostream>
using namespace std;

class AquaMonstera : public Monstera
{
private:
	double fDamageConversion;

public:
	// Default constructor
	AquaMonstera();

	// Parameterised constructor
	AquaMonstera(string aName, double aMaxHp, double aMaxMp,
		Rarity aRarity, int aStamina, double aMinDamage, double aMaxDamage,
		double aMinDefense, double aMaxDefense, int aLevel, double aDamageConversion);

	// Clone current object, similar to copy constructor
	virtual AquaMonstera* Clone() const override;

	// Getter and setter for damage conversion
	double getDamageConversion() const;
	void setDamageConversion(double aDamage);

	// Unique skill
	void Heal();

	// Override virtual functions from Monstera
	void TakeDamage(double aDamage, Monstera& aTarget) override;
	void BattleOptions(Monstera* aTarget) override;
	void Attack(Monstera& aTarget) override;

	// AI behaviour
	void ExecuteBehaviorTree(BTree* root, Monstera* player) override;
	void ExecuteAction(string action, Monstera* player) override;

	// Function to serialize player data to an output stream
	void serialise(std::ostream& out) const;

	// Function to deserialize player data from an input stream
	void deserialise(std::istream& in);

	// Destructor
	~AquaMonstera();
};