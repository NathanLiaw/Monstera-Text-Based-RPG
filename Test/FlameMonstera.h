#pragma once
#include "Monstera.h"
#include "Element.h"
#include "Rarity.h"
#include <iostream>
#include "BTree.h"
using namespace std;

class FlameMonstera : public Monstera
{
private:
	double fDamageReflection;
	bool fImmolation;

public:
	// Default constructor
	FlameMonstera();

	// Parameterised constructor
	FlameMonstera(string aName, double aMaxHp, double aMaxMp,
		Rarity aRarity, int aStamina, double aMinDamage, double aMaxDamage,
		double aMinDefense, double aMaxDefense, int aLevel, double aDamageReflection);
	
	// Clone current object, similar to copy constructor
	virtual FlameMonstera* Clone() const override;

	// Getter and setter for fields
	double getDamageReflection() const;
	void setDamageReflection(double aDamage);
	bool getImmolation() const;
	void setImmolation();

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
	~FlameMonstera();
};