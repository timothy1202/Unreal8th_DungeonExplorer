#pragma once
#include "Item.h"
#include "ItemManager.h"

//Factory Pattern

class ItemFactory
{
public:

    static Item CreateItem(int id, int amount = 1)
    {
        Item* masterData = ItemManager::GetInstance().GetItemById(id);
        if (!masterData) return Item();

        // create a base copy
        Item newItem = *masterData;
        newItem.count = amount;

        // Individual Detailization (Example: Random Stat)
        // Only apply for Weapons
        //if (newItem.type == ItemType::Weapon)
        //{
        //    // Add a random bonus between 0 and 3
        //    int bonus = rand() % 6;
        //    // Change name if it has a high bonus
        //    if (bonus >= 3) 
        //    {
        //        newItem.value += bonus;
        //        newItem.name = "Sharp " + newItem.name;
        //    }
        //}

        return newItem;
    }
};