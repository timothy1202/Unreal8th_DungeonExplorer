#pragma once
#include <vector>
#include "Item.h"
#include "Character.h"

enum class EquipSlot 
{
    Weapon = 0, // Slot for offensive gear
    Armor = 1,  // Slot for defensive gear
    Max = 2     // Total number of equipment slots
};

class Inventory 
{
private:
    // Container for owned items
    std::vector<Item> ownedItems;
    int equippedSlots[(int)EquipSlot::Max];
    int tempAtkBuff = 0;

public:
    Inventory() 
    {
        // Initialize all slots to nullptr
        for (int i = 0; i < (int)EquipSlot::Max; ++i) 
        {
            equippedSlots[i] = -1;
        }
    }

    // Add a copy of an item to the inventory
    void AddItem(const Item& newItem);

    // Display all items in a formatted list
    void ShowInventory() const;

    // Get the number of items currently held
    int GetItemCount() const;

    //Use one item
    void UseItem();
    void UseItem(int itemId);

    void EquipItem(int index);

    void SetColor(int color)const;

    std::string PrintByRarity(Item item) const;

    std::vector<Item>& GetOwnedItems() { return ownedItems; }

    void RemoveItem(int index);

    int GetTempAtkBuff() { return tempAtkBuff; }

    void SetTempAtkBuff(int buff);

    void UnequipSlot(int slotIndex);
};