#include "Shop.h"

// Parameterised constructor 
Shop::Shop(List* monsteras, Objective* objectives)
{
	fNormal = new Gacha("Normal", monsteras, 6, 2, 2, 15);
	fEpic = new Gacha("Epic", monsteras, 2, 6, 2, 30);
	fLegendary = new Gacha("Legendary", monsteras, 2, 2, 6, 50);
	fObjectives = objectives;
}

// Function to open the shop and allow the player to interact with it
void Shop::OpenShop(Player* player)
{
	Monstera* temp;
	string name = "";
	string gachaType = "";
	int userInput = 0;
	int option = 0;
	while (userInput != 4)
	{
		cout << "Welcome! How can I help you today? " << endl;
		cout << "[1] Open Gacha" << endl;
		cout << "[2] Upgrade my Monstera" << endl;
		cout << "[3] Sell my Monstera" << endl;
		cout << "[4] Exit" << endl;
		cin >> userInput;
		if (userInput == 1)
		{
			cout << "Which Gacha would you like to spin?" << endl;
			cout << "[1] Normal (15 coins)" << endl;
			cout << "[2] Epic (30 coins)" << endl;
			cout << "[3] Legendary (50 coins)" << endl;
			cout << "[4] Exit" << endl;
			cin >> option;
			if (option == 1 && player->getCoins() - 15 >= 0)
			{
				player->setCoins(player->getCoins() - 15);
				gachaType = "Normal";
			}
			else if (option == 2 && player->getCoins() - 30 >= 0)
			{
				player->setCoins(player->getCoins() - 30);
				gachaType = "Epic";
			}
			else if (option == 3 && player->getCoins() - 50 >= 0)
			{
				player->setCoins(player->getCoins() - 50);
				gachaType = "Legendary";
			}
			else
			{
				cout << "Sorry. Insufficient coins." << endl;
			}

			temp = (*this->getGacha(gachaType).Roll()).Clone();

			// If the player already has this Monstera, refund 50% cost and +5exp to the Monstera with the same name
			if (player->HasMonstera(temp->getName()))
			{
				int refund = this->getGacha(gachaType).getCost() * 0.5;
				cout << "Seems like you already have this Monstera." << endl;
				cout << "50% refunded and add 5 exp to the existing Monstera (+" << refund << "coins)" << endl;
				player->setCoins(player->getCoins() + refund);
				player->getMonstera(temp->getName()).LevelUp(5);
			}
			else
			{
				player->AddMonstera(temp);
			}
			cout << fObjectives->ClearObjective(player, 1) << endl;

		}
		else if (userInput == 2)
		{
			if (player->getInventory().size() > 0)
			{
				cout << "Select a Monstera" << endl;
				player->ViewMonsteras();
				cin >> option;
				this->Upgrade(player->getMonstera(option).getName(), player);
				cout << fObjectives->ClearObjective(player, 3) << endl;;
			}
			else
			{
				cout << "It seems that you do not have any Monstera yet" << endl;
			}
		}
		else if (userInput == 3)
		{
			int idx = 1;
			cout << "Select which Monstera to sell:" << endl;
			cout << "Normal: 10 coins" << endl;
			cout << "Epic: 20 coins" << endl;
			cout << "Legendary: 30 coins" << endl;
			player->ViewMonsteras();
			cin >> idx;
			player->RemoveMonstera(idx);
			cout << player->getMonstera(idx).getName() << " has been sold." << endl;
			if (player->getMonstera(idx).RarityToString() == "Normal")
			{
				player->setCoins(player->getCoins() + 10);
				cout << "+10 coins";
			}
			else if (player->getMonstera(idx).RarityToString() == "Epic")
			{
				player->setCoins(player->getCoins() + 20);
				cout << "+20 coins";
			}
			else if (player->getMonstera(idx).RarityToString() == "Legendary")
			{
				player->setCoins(player->getCoins() + 30);
				cout << "+30 coins";
			}
		}
		else if (userInput == 4)
		{
			break;
		}
		else
		{
			cout << "Invalid input" << endl;
		}
	}
	cout << "Thank you. Please come again." << endl;
}

// Function to upgrade a Monstera in the player's inventory
void Shop::Upgrade(string aName, Player* player)
{
	string userInput = "";
	cout << "Select an upgrade for your Monstera: " << endl;
	cout << "[1]. +30exp (10 coins)" << endl;
	cout << "[2]. +330exp (100 coins)" << endl;
	cin >> userInput;
	if (userInput == "1" && player->getCoins() - 10 >= 0)
	{
		player->getMonstera(aName).LevelUp(30);
	}
	else if (userInput == "2" && player->getCoins() - 15 >= 0)
	{
		player->getMonstera(aName).LevelUp(330);
	}
	else
	{
		cout << "Sorry. Insufficient coins" << endl;
	}
}

// Function to get a reference to a specific gacha based on its name
Gacha& Shop::getGacha(string aName)
{
	if (aName == "Legendary")
	{
		return *fLegendary;
	}
	else if (aName == "Epic")
	{
		return *fEpic;
	}
	else
	{
		return *fNormal;
	}
}

// Destructor 
Shop::~Shop()
{
	delete fNormal;
	delete fEpic;
	delete fLegendary;
}
