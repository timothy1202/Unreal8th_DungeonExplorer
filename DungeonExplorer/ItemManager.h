#pragma once
#include <vector>
#include <map>
#include "Item.h"

class ItemManager 
{
private:
    // Keep the original data of all items by ID
    std::map<int, Item> itemDatabase;
    ItemManager() {}

public:
    //Singleton Pattern
    static ItemManager& GetInstance() 
    {
        static ItemManager instance; 
        return instance;
    }
    // Deleted copy constructor and assignment operator to ensure a single instance
    ItemManager(const ItemManager&) = delete;
    void operator=(const ItemManager&) = delete;

    void Initialize(); // Register items with hardcoding here

    // Retrieve a pointer to an item's master data by ID
    Item* GetItemById(int id);

    // Get a list of all items for display or debugging
    const std::map<int, Item>& GetFullDatabase() const;
};