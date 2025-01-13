#include "TerraMonstera.h"

// Default constructor
TerraMonstera::TerraMonstera() : Monstera()
{
    fDamageReduction = 1;
    this->setElement(Element::Terra);
    fGaiaSap = false;
}

// Parameterised constructor
TerraMonstera::TerraMonstera(string aName, double aMaxHp, double aMaxMp,
    Rarity aRarity, int aStamina, double aMinDamage, double aMaxDamage,
    double aMinDefense, double aMaxDefense, int aLevel, double aDamageReduction)
    : Monstera(aName, aMaxHp, aMaxMp, aRarity, aStamina, aMinDamage, aMaxDamage,
        aMinDefense, aMaxDefense, aLevel), fDamageReduction(aDamageReduction)
{
    this->setElement(Element::Terra);
    fGaiaSap = false;
}

// Clone current object
TerraMonstera* TerraMonstera::Clone() const
{
    return new TerraMonstera(*this);
}

// Getter for damageConversion
double TerraMonstera::getDamageReduction() const
{
    return fDamageReduction;
}

// Setter for damageConversion
void TerraMonstera::setDamageReduction(double aDamage)
{
    fDamageReduction = aDamage;
}

// Take damage
void TerraMonstera::TakeDamage(double aDamage, Monstera& aTarget)
{
    // Reduce damage taken by total damage reduction from fDamageReduction
    double totalDamage = aDamage - this->getDamagedBlocked() - fDamageReduction;
    if (totalDamage < 0)
    {
        totalDamage = 0;
    }
    double newHp = this->getHp() - (totalDamage);

    // Add 1% of damage taken to total damage reduction
    fDamageReduction += aDamage * 0.01;
    
    if (this->getDamagedBlocked() > 0)
    {
        cout << this->getName() << " blocked " << this->getDamagedBlocked() << "dmg" << endl;

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

// Attack
void TerraMonstera::Attack(Monstera& aTarget)
{
    double damage = this->RollValue(this->getMinDamage(), this->getMaxDamage());
    if (this->getStamina() - 3 >= 0)
    {
        // If gaia sap is on, check if condition fulfills else turn it off
        if (fGaiaSap == true)
        {
            if (this->getMp() - 5 >= 0)
            {
                // Lifesteal: Gain 5% hp of damage dealt
                int newHp = this->getHp() + (damage * 0.5);
                this->setMp(this->getMp() - 7);
            }
            else
            {
                this->getGaiaSap();
            }
        }
        cout << this->getName() << " is dealing " << damage << " damage to " << aTarget.getName() << endl;

        aTarget.TakeDamage(damage, aTarget);

        this->setStamina(this->getStamina() - 3);
    }
    else
    {
        cout << "Insufficient stamina. Turn wasted." << endl;
    }
}

// Get state of gaia sap
bool TerraMonstera::getGaiaSap() const
{
    return fGaiaSap;
}

// Turn GaiaSap on or off. Costs 7mp and get 5% lifesteal.
void TerraMonstera::setGaiaSap()
{
    if (this->getStamina() - 1 >= 0)
    {
        if (fGaiaSap == false)
        {
            cout << "GaiaSap On: Gain 5% lifesteal on every attack at the cost of 7mp (-1 stamina)" << endl;
            fGaiaSap = true;
            this->setStamina(this->getStamina() - 1);
        }
        else
        {
            cout << "GaiaSap Off: No longer gain 5% lifesteal" << endl;
            fGaiaSap = false;
        }
    }
    else
    {
        // If player try to use this without having the mana, it will automatically rest instead.
        cout << "Insufficient mana. Resting..." << endl;
        this->Rest();
        fGaiaSap = false;
    }

}

// Battle options allow player to view the possible actions and take those actions
void TerraMonstera::BattleOptions(Monstera* aTarget)
{
    int userInput = 0;
    cout << "Passive: Reduce damage taken by total of 5% of each damage taken cumulatively" << endl;
    cout << "1. Attack: " << this->getMinDamage() << "-" << this->getMaxDamage() << "dmg (-3 stamina)" << endl;
    cout << "2. Block: " << this->getMinDefense() << "-" << this->getMaxDefense() << "dmg (-2 stamina, +2mp)" << endl;
    cout << "3. Rest: Regain stamina and mana (+1 stamina, +5mp)" << endl;
    cout << "4. Dodge: 30% chance to dodge an attack completely (-1 stamina, +3mp if successful)" << endl;
    cout << "5. Gaia Sap: +Lifesteal 5% (-1 stamina once, -7mp every round)" << endl;
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
        this->setGaiaSap(); 
        break;
    default:
        this->Rest();
        break;
    }

}

// Function to execute the behavior tree
void TerraMonstera::ExecuteBehaviorTree(BTree* root, Monstera* player) {
    string attack = "Attack";
    string block = "Block Damage";
    string dodge = "Dodge";
    string rest = "Rest";
    string gaiasap = "Gaia Sap";

    if (root == &BTree::NIL) {
        return;
    }

    if (root->key() == "High Stamina") {
        if (getStamina() > 3 && getGaiaSap() == false && getMp() > 20) {
            ExecuteAction(gaiasap, player);
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
        else if (getStamina() - 3 >= 0 && player->getStamina() > 3)
        {
            ExecuteAction(attack, player);
        }
        else if (getStamina() < 5 && player->getStamina() < 5)
        {
            ExecuteAction(rest, player);
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
    }

    // Pre Order Traversal (Current Node, Left, Right)
    // Recursively evaluate left subtree
    ExecuteBehaviorTree(&root->left(), player);

    // Recursively evaluate right subtree
    ExecuteBehaviorTree(&root->right(), player);
}

// Function to execute actions based on the met condition
void TerraMonstera::ExecuteAction(string action, Monstera* player) {
    string gaiasap = "Gaia Sap";
    string block = "Block Damage";
    string rest = "Rest";
    string attack = "Attack";
    string dodge = "Dodge";

    if (action == gaiasap) {
        setGaiaSap();
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

// Serialize function for TerraMonstera
void TerraMonstera::serialise(std::ostream& out) const {
    Monstera::serialise(out);

    out << " " << fDamageReduction;
}

// Deserialize function for FlameMonstera
void TerraMonstera::deserialise(std::istream& in) {
    Monstera::deserialise(in);

    in >> fDamageReduction;
}

// Destructor
TerraMonstera::~TerraMonstera()
{

}