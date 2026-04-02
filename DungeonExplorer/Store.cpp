#include "Store.h"
#include "LogSystem.h"
#include <sstream>

using namespace std;

Store::Store() {}

void Store::InitializeStore()
{
    shopItemIDs.push_back(101); // Rusty Dagger
    shopItemIDs.push_back(102); // Iron Sword
    shopItemIDs.push_back(103); // Great Axe

    shopItemIDs.push_back(201); // Cloth Tunic
    shopItemIDs.push_back(202); // Leather Armor
    shopItemIDs.push_back(203); // Plate Mail

    shopItemIDs.push_back(301); // Red Potion
    shopItemIDs.push_back(302); // Greater Red Potion
    shopItemIDs.push_back(303); // Power Potion
    shopItemIDs.push_back(304); // Greater Power Potion
}

void Store::ShowShopMenu(int playerGold) const
{
    vector<string> Inputs;
    stringstream SS;
    SS.str("");
    for (size_t i = 0; i < shopItemIDs.size(); ++i)
    {
        Item* item = ItemManager::GetInstance().GetItemById(shopItemIDs[i]);
        if (item)
        {
            SS.str("");
            SS << "[" << i + 1 << "] " << item->name << " | Price: " << item->price << " G";
            Inputs.push_back(SS.str());
        }
    }
    LogSystem::PrintStringsOnMain(Inputs);
}

void Store::BuyItem(int selection, int& playerGold, Inventory& playerInventory)
{
    int index = selection - 1;
    if (index < 0 || index >= (int)shopItemIDs.size()) return;

    int itemId = shopItemIDs[index];
    Item* masterData = ItemManager::GetInstance().GetItemById(itemId);

    //
    // Check if player has enough gold
    if (playerGold >= masterData->price)
    {
        playerGold -= masterData->price;
        // Create a new item instance and add to inventory
        playerInventory.AddItem(ItemFactory::CreateItem(itemId));
        stringstream SS;
        SS.str("");
        SS << "[System] Purchase success! Current Gold: " << playerGold << " G" << endl;
        LogSystem::PrintStringsOnLog({ SS.str() });
    }
    else
    {
        LogSystem::PrintStringsOnLog({ "[System] Not enough gold!" });
    }
}

void Store::SellItem(int selection, int& playerGold, Inventory& playerInventory)
{
    // 1. Convert user selection to vector index
    int index = selection - 1;

    std::vector<Item>& items = playerInventory.GetOwnedItems();

    if (index < 0 || index >= (int)items.size())
    {
        LogSystem::PrintStringsOnLog({ "[System] Invalid inventory number!" });
        return;
    }

    Item& itemToSell = items[index];
    int refund = static_cast<int>(itemToSell.price * sellReturnRate);

    playerGold += refund;
    stringstream SS;
    SS << "[System] Sold " << itemToSell.name << " for " << refund << " G." << endl;
    LogSystem::PrintStringsOnLog({SS.str()});

    playerInventory.RemoveItem(index);
}