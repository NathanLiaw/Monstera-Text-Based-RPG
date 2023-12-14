#include "AquaMonstera.h"

// Default constructor
AquaMonstera::AquaMonstera() : Monstera()
{
    fDamageConversion = 1;
    this->setElement(Element::Aqua);
}

// Parameterised constructor
AquaMonstera::AquaMonstera(string aName, double aMaxHp, double aMaxMp,
    Rarity aRarity, int aStamina, double aMinDamage, double aMaxDamage,
    double aMinDefense, double aMaxDefense, int aLevel, double aDamageConversion)
    : Monstera(aName, aMaxHp, aMaxMp, aRarity, aStamina, aMinDamage, aMaxDamage,
        aMinDefense, aMaxDefense, aLevel), fDamageConversion(aDamageConversion)
{
    this->setElement(Element::Aqua);
}

// Clone current object, a copy constructor
AquaMonstera* AquaMonstera::Clone() const {
    return new AquaMonstera(*this);
}

// Getter for damageConversion
double AquaMonstera::getDamageConversion() const
{
    return fDamageConversion;
}

// Setter for damageConversion
void AquaMonstera::setDamageConversion(double aDamage)
{
    fDamageConversion = aDamage;
}

// A function to take damage from another Monstera
void AquaMonstera::TakeDamage(double aDamage, Monstera& aTarget)
{
    double totalDamage = aDamage - this->getDamagedBlocked() > 0 ? aDamage - this->getDamagedBlocked() : 1;
    double newHp = this->getHp() - (totalDamage);

    if (this->getDamagedBlocked() > 0)
    {
        cout << this->getName() << " blocked " << this->getDamagedBlocked() << "dmg" << endl;

        // Convert 5% of damage into defense
        fDamageConversion += aDamage * 0.05;
        this->setMinDefense(this->getMinDefense() + fDamageConversion);
        this->setMaxDefense(this->getMaxDefense() + fDamageConversion);
    
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

// A function to attack another Monstera 
void AquaMonstera::Attack(Monstera& aTarget)
{
    double damage = this->RollValue(this->getMinDamage(), this->getMaxDamage());
    if (this->getStamina() - 3 >= 0)
    {
        cout << this->getName() << " is dealing " << damage << " damage to " << aTarget.getName() << endl;

        aTarget.TakeDamage(damage, aTarget);

        this->setStamina(this->getStamina() - 3);
    }
    else
    {
        cout << "Insufficient stamina. Turn wasted." << endl;
    }
}

// Heal 30hp at the cost of 3 stamina and 20mp
void AquaMonstera::Heal()
{
    if (this->getMp() - 20 >= 0 && this->getHp() != this->getMaxHp() && this->getStamina() - 3 >= 0)
    {
        cout << "+30Hp" << endl;
        this->setMp(this->getMp() - 20);
        int newHp = this->getHp() + 30;
        if (newHp > this->getMaxHp())
        {
            newHp = this->getMaxHp();
        }
        this->setHp(newHp);
        this->setStamina(this->getStamina() - 3);
    }
    else if (this->getHp() == this->getMaxHp())
    {
        cout << "Hp is already full" << endl;
    }
    else
    {
        cout << "Insufficient stamina. Turn wasted" << endl;
    }
}

// Battle options allow player to view the possible actions and take those actions
void AquaMonstera::BattleOptions(Monstera* aTarget)
{
    int userInput = 0;
    cout << "Passive: Reduce damage taken by total of 5% of each damage taken cumulatively" << endl;
    cout << "1. Attack: " << this->getMinDamage() << "-" << this->getMaxDamage() << "dmg (-3 stamina)" << endl;
    cout << "2. Block: " << this->getMinDefense() << "-" << this->getMaxDefense() << "dmg (-2 stamina, +2mp)" << endl;
    cout << "3. Rest: Regain stamina and mana (+1 stamina, +5mp)" << endl;
    cout << "4. Dodge: 30% chance to dodge an attack completely (-1 stamina, +3mp if successful)" << endl;
    cout << "5. Heal: +30hp (-3 stamina, -20mp)" << endl;
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
        this->Heal();
        break;
    default:
        this->Rest();
        break;
    }
}

// Function to execute the behavior tree
void AquaMonstera::ExecuteBehaviorTree(BTree* root, Monstera* player) {
    string attack = "Attack";
    string block = "Block Damage";
    string dodge = "Dodge";
    string rest = "Rest";
    string heal = "Heal";

    if (root == &BTree::NIL) {
        return;
    }
    
    if (root->key() == "High Stamina") {
        if (getStamina() > 3 && getMp() > 15) {
            ExecuteAction(attack, player);
            return;
        }
        else if (getStamina() > 5)
        {
            ExecuteAction(attack, player);
            return;
        }
    }
    else if (root->key() == "Sufficient Stamina") {
        if (getStamina() == 3 && player->getStamina() < 3) {
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
        if (getHp() > 40 && getStamina() > 3) {
            ExecuteAction(attack, player);
            return;
        }
    }
    else if (root->key() == "Low Hp") {
        if (player->getHp() <= getMinDamage() && getStamina() < 3) {
            ExecuteAction(rest, player);
            return;
        }
        else if (getHp() <= 40 && player->getStamina() >= 3)
        {
            ExecuteAction(dodge, player);
        }
        else if (getStamina() > 2 && getHp() <= 50 && getMp() >= 20)
        {
            ExecuteAction(heal, player);
        }
    }

    // Recursively evaluate left subtree
    ExecuteBehaviorTree(&root->left(), player);

    // Recursively evaluate right subtree
    ExecuteBehaviorTree(&root->right(), player);
}

// Function to execute actions based on the met condition
void AquaMonstera::ExecuteAction(string action, Monstera* player) {
    string heal = "Heal";
    string block = "Block Damage";
    string rest = "Rest";
    string attack = "Attack";
    string dodge = "Dodge";

    if (action == heal) {
        Heal();
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

// Serialize function for AquaMonstera
void AquaMonstera::serialise(std::ostream& out) const {
    Monstera::serialise(out);

    out << " " << fDamageConversion;
}

// Deserialize function for AquaMonstera
void AquaMonstera::deserialise(std::istream& in) {
    Monstera::deserialise(in);

    in >> fDamageConversion;
}

AquaMonstera::~AquaMonstera()
{

}