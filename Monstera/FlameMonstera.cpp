#include "FlameMonstera.h"

// Default constructor
FlameMonstera::FlameMonstera() : Monstera()
{
    fDamageReflection = 1;
    this->setElement(Element::Flame);
    fImmolation = false;
}

// Parameterised constructor
FlameMonstera::FlameMonstera(string aName, double aMaxHp, double aMaxMp,
    Rarity aRarity, int aStamina, double aMinDamage, double aMaxDamage,
    double aMinDefense, double aMaxDefense, int aLevel, double aDamageReflection)
    : Monstera(aName, aMaxHp, aMaxMp, aRarity, aStamina, aMinDamage, aMaxDamage,
        aMinDefense, aMaxDefense, aLevel), fDamageReflection(aDamageReflection)
{
    this->setElement(Element::Flame);
    fImmolation = false;
}

// Clone function
FlameMonstera* FlameMonstera::Clone() const
{
    return new FlameMonstera(*this);
}

// Getter for damageConversion
double FlameMonstera::getDamageReflection() const
{
    return fDamageReflection;
}

// Setter for damageConversion
void FlameMonstera::setDamageReflection(double aDamage)
{
    fDamageReflection = aDamage;
}

// Take damage
void FlameMonstera::TakeDamage(double aDamage, Monstera& aTarget)
{
    double newHp = this->getHp() - (aDamage - this->getDamagedBlocked());

    // Reflect 5% damage taken back to the enemy
    if (this->getDamagedBlocked() > 0)
    {
        cout << this->getName() << " blocked " << this->getDamagedBlocked() << "dmg" << endl;

        // Deals 5% damage to enemy
        this->setDamageReflection(this->getDamageReflection() + 0.05 * aDamage);
        cout << this->getName() << " is reflecting 5% damage back (-" << this->getDamageReflection() << ")" << endl;
        aTarget.setHp(aTarget.getHp() - 0.05 * aDamage);

        // Reset damage blocked to 0
        this->setDamageBlocked(0);
    }

    // Gain 5% mana from taking damage
    int newMp = this->getMp() + (aDamage * 0.05);
    if (newMp > this->getMaxMp())
    {
        newMp = this->getMaxMp();
    }
    this->setMp(newMp);

    this->setHp((newHp >= 0) ? newHp : 0);
}

// Attack a target
void FlameMonstera::Attack(Monstera& aTarget)
{
    double damage = this->RollValue(this->getMinDamage(), this->getMaxDamage());
    if (this->getStamina() - 3 >= 0)
    {
        // If immolation is activated
        if (this->fImmolation == true)
        {
            // If sufficient hp and mp, deals 100% more damage, else turn off immolation and deal normal attack
            if (this->getMp() - 5 >= 0 && this->getHp() - 2 >= 0)
            {
                damage += 0.5 * damage;
                this->setHp(this->getHp() - 2);
                this->setMp(this->getMp() - 5);
                cout << "Immolation is on. Deals 50% more damage. (-2hp, -5mp)" << endl;
            }
            else
            {
                cout << "Insufficient hp or mp. Turning off Immolation." << endl;
                this->setImmolation();
            }
        }
        // Deduct 3 stamina
        this->setStamina(this->getStamina() - 3);
        cout << this->getName() << " is dealing " << damage << " damage to " << aTarget.getName() << endl;

        // Enemy take damage
        aTarget.TakeDamage(damage, aTarget);
    }
    else
    {
        cout << "Insufficient stamina. Turn wasted." << endl;
    }

    // Gain 50% mana from dealing damage
    int newMp = this->getMp() + (damage * 0.5);
    if (newMp > this->getMaxMp())
    {
        newMp = this->getMaxMp();
    }
    this->setMp(newMp);
}

// Get state of immolation
bool FlameMonstera::getImmolation() const
{
    return fImmolation;
}

// Turn immolation on or off. Costs 2hp and 5mp each turn while it is on but deals 100% more damage.
void FlameMonstera::setImmolation()
{
    if (fImmolation == false && this->getHp() - 2 > 0 && this->getMp() - 5 >= 0 && this->getStamina() - 1 >= 0)
    {
        cout << "Immolation On: Sacrifice 2hp and 5mp to deal 100% more damage to the enemy." << endl;
        fImmolation = true;
        this->setStamina(this->getStamina() - 1);
    }
    else
    {
        cout << "Immolation Off" << endl;
        fImmolation = false;
    }

    if (fImmolation == false && this->getMp() - 5 <= 0)
    {
        cout << "Insufficient hp or mana. Resting instead..." << endl;
        this->Rest();
    }
}

// Battle options allow player to view the possible actions and take those actions
void FlameMonstera::BattleOptions(Monstera* aTarget)
{
    int userInput = 0;
    cout << "Passive: Reduce damage taken by total of 5% of each damage taken cumulatively" << endl;
    cout << "1. Attack: " << this->getMinDamage() << "-" << this->getMaxDamage() << "dmg (-3 stamina)" << endl;
    cout << "2. Block: " << this->getMinDefense() << "-" << this->getMaxDefense() << "dmg (-2 stamina, +2mp)" << endl;
    cout << "3. Rest: Regain stamina and mana (+1 stamina, +5mp)" << endl;
    cout << "4. Dodge: 30% chance to dodge an attack completely (-1 stamina, +3mp if successful)" << endl;
    cout << "5. Immolation: Deals 100% more damage to enemy (-1 stamina once, -2hp, -5mp)" << endl;
    cin >> userInput;

    cout << "Player's Actions: ";

    switch (userInput)
    {
    case 1:
        this->Attack(*aTarget);
        break;
    case 2:
        this->BlockDamage();
        break;
    case 3:
        this->Rest();
        break;
    case 4:
        this->Dodge();
        break;
    case 5:
        this->setImmolation();
        break;
    default:
        this->Rest();
        break;
    }
}

// Function to execute the behavior tree
void FlameMonstera::ExecuteBehaviorTree(BTree* root, Monstera* player) {
    string attack = "Attack";
    string block = "Block Damage";
    string dodge = "Dodge";
    string rest = "Rest";
    string immolation = "Immolation";

    if (root == &BTree::NIL) {
        return;
    }

    if (root->key() == "High Stamina") {
        if (getStamina() > 5 && getImmolation() == false && getMp() > 14) {
            ExecuteAction(immolation, player);
            return;
        }
        else if (getStamina() > 5)
        {
            ExecuteAction(attack, player);
            return;
        }
    }
    else if (root->key() == "Sufficient Stamina") {
        if (getStamina() >= 3 && player->getStamina() < 3) {
            int random = rand() % 2;
            if (random == 0 && player->getHp() >= getMinDamage())
            {
                ExecuteAction(rest, player);
            }
            else
            {
                ExecuteAction(attack, player);
            }
            return;
        }
    }
    else if (root->key() == "Low Stamina") {
        if (getStamina() > 1 && getStamina() % 2 == 0 && player->getStamina() % 2 == 1 && player->getStamina() >= 3 || 
            (getStamina() > 1 && getStamina() < 3 && player->getHp() >= getMinDamage())) 
        {
            ExecuteAction(block, player);
            return;
        }
        else if (getStamina() - 3 >= 0)
        {
            ExecuteAction(attack, player);
        }
    }
    else if (root->key() == "High Hp") {
        if (getHp() > 40) {
            ExecuteAction(attack, player);
            return;
        }
    }
    else if (root->key() == "Low Hp") {
        if (getHp() <= 40 && player->getHp() <= getMinDamage()) {
            ExecuteAction(rest, player);
            return;
        }
        else if (getHp() <= 40 && player->getStamina() >= 3)
        {
            ExecuteAction(dodge, player);
        }
    }
    else
    {
        ExecuteAction(rest, player);
    }

    // Recursively evaluate left subtree
    ExecuteBehaviorTree(&root->left(), player);
    
    // Recursively evaluate right subtree
    ExecuteBehaviorTree(&root->right(), player);
}

// Function to execute actions based on the met condition
void FlameMonstera::ExecuteAction(string action, Monstera* player) {
    string immolation = "Immolation";
    string block = "Block Damage";
    string rest = "Rest";
    string attack = "Attack";
    string dodge = "Dodge";

    if (action == immolation) {
        setImmolation();
    }
    else if (action == block) {
        BlockDamage();
    }
    else if (action == rest) {
        Rest();
    }
    else if (action == attack) {
        Attack(*player);
    }
    else if (action == dodge) {
        Dodge();
    }

    else {
        cout << "Unknown action: " << action << endl;
    }
}

// Serialize function for FlameMonstera
void FlameMonstera::serialise(std::ostream& out) const {
    Monstera::serialise(out);

    out << " " << fDamageReflection;
}

// Deserialize function for FlameMonstera
void FlameMonstera::deserialise(std::istream& in) {
    Monstera::deserialise(in);

    in >> fDamageReflection;
}

FlameMonstera::~FlameMonstera()
{

}