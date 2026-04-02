#pragma once
#include <vector>
#include <iostream>
#include "ItemManager.h"
#include "Inventory.h"
#include "ItemFactory.h"

class Store
{
private:
    std::vector<int> shopItemIDs; // List of item IDs available in the shop
    const float sellReturnRate = 0.6f; // 60% return rate for selling items

public:
    Store();

    // Initialize shop with default item list
    void InitializeStore();

    // Display shop items and player's current gold
    void ShowShopMenu(int playerGold) const;

    // Process item purchase
    void BuyItem(int selection, int& playerGold, Inventory& playerInventory);

    // Process item sale from inventory
    void SellItem(int selection, int& playerGold, Inventory& playerInventory);

};