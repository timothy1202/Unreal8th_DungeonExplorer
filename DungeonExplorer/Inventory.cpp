#include <windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "LogSystem.h"
#include "Inventory.h"

using namespace std;

void Inventory::AddItem(const Item& newItem) 
{
    stringstream SS;
    for (auto it = ownedItems.begin(); it != ownedItems.end(); ++it)
    {
        if (it->id == newItem.id)
        {
            it->count += newItem.count;
            SS.str("");
            SS << "[System] " << newItem.name << " stack increased to " << it->count << ".";
            LogSystem::PrintStringsOnLog({ SS.str()});
            return;
        }
    }
    ownedItems.push_back(newItem);
    SS.str("");
    SS << "[System] Added " << newItem.name << " to inventory.";
    LogSystem::PrintStringsOnLog({ SS.str() });
}

void Inventory::ShowInventory() const
{
    vector<string> Input = {};
    stringstream SS;
    Input.push_back("--- Current Inventory ---");

    if (ownedItems.empty()) 
    {
        Input.push_back("(Empty)");
        LogSystem::PrintStringsOnMain(Input);
        return;
    }

    for (size_t i = 0; i < ownedItems.size(); ++i)
    {
        SS.str("");
        SS << "[" << i + 1 << "] " 
            << PrintByRarity(ownedItems[i]) 
            << " (x" << ownedItems[i].count << ")"
            << " | " << ownedItems[i].desc;
        Input.push_back(SS.str());
        
    }
    LogSystem::PrintStringsOnMain(Input);
}

int Inventory::GetItemCount() const { return static_cast<int>(ownedItems.size()); }

void Inventory::UseItem() {
    if (ownedItems.empty()) {
        LogSystem::PrintStringsOnLog({"[System] Inventory is empty."});
        return;
    }

    cout << TextFormat::CYAN << "Enter Item Name: " << TextFormat::DEFAULT;
    std::string itemName;
    std::cin.ignore();
    std::getline(std::cin, itemName);

    for (auto it = ownedItems.begin(); it != ownedItems.end(); ++it) 
    {
        if (it->name == itemName) 
        {
            // 1. Get the already created player instance
            Character* player = Character::GetInstance();

            if (player == nullptr) 
            {
                LogSystem::PrintStringsOnLog({"[Error] Player not found. Create character first!"});
                return;

            }

            if (it->type == ItemType::Potion) 
            {
                stringstream SS;
                SS << "[System] Used " << it->name << "!";
                LogSystem::PrintStringsOnLog({ SS.str() });

                // 2. HP Recovery logic
                if (it->id == 301 || it->id == 302) 
                {
                    SS.str("");
                    int finalHP = player->GetHP() + it->value;
                    if (finalHP > player->GetMaxHP()) finalHP = player->GetMaxHP();
                    player->SetHP(finalHP);
                    SS << "[Effect] HP is now " << player->GetHP();
                    LogSystem::PrintStringsOnLog({ SS.str() });
                }
                // 3. Temporary Attack Boost logic
                else if (it->id == 303 || it->id == 304) 
                {
                    SS.str("");
                    player->SetAttack(player->GetAttack() + it->value);
                    this->tempAtkBuff = it->value; // add temp attack buff
                    SS << "[Effect] Attack boosted by " << it->value << "!" << " temporarily for this stage!";
                    LogSystem::PrintStringsOnLog({ SS.str() });
                }

                // 4. Consume item
                if (it->count > 1) it->count--;
                else ownedItems.erase(it);
            }
            else {
                vector<string> WarningLog = { itemName + " can't use" };
                LogSystem::PrintStringsOnLog(WarningLog);
            }
            return;
        }
    }
    LogSystem::PrintStringsOnLog({"[System] Item not found."});
}

void Inventory::UseItem(int num) 
{
    if (ownedItems.empty()) 
    {
        LogSystem::PrintStringsOnLog({ "[System] Inventory is empty." });
        return;
    }

    for (auto it = ownedItems.begin(); it != ownedItems.end(); ++it)
    {
            Character* player = Character::GetInstance();
            if (player == nullptr) return;

            if (it->type == ItemType::Potion && (it->id == 301 || it->id == 302))
            {

                while (player->GetHP() < player->GetMaxHP() && it->count > 0)
                {
                    int healAmount = it->value;
                    int currentHP = player->GetHP();
                    int maxHP = player->GetMaxHP();

                    int finalHP = (currentHP + healAmount > maxHP) ? maxHP : currentHP + healAmount;
                    player->SetHP(finalHP);

                    it->count--; 
                }

                stringstream SS;
                SS << "[Effect] HP is now fully restored or optimized: " << player->GetHP();
                LogSystem::PrintStringsOnLog({ SS.str() });

                if (it->count <= 0) 
                {
                    it = ownedItems.erase(it);
                }
                else 
                {
                    ++it;
                }
                return; 
            }
    }
}

void Inventory::UnequipSlot(int slotIndex)
{
    if (equippedSlots[slotIndex] == -1) return;

    Character* player = Character::GetInstance();
    int oldItemId = equippedSlots[slotIndex];
    stringstream SS;

    for (auto& item : ownedItems)
    {
        if (item.id == oldItemId)
        {
            item.equiped = false;

            if (item.type == ItemType::Weapon)
            {
                player->SetAttack(player->GetAttack() - item.value);
                SS << "[System] Unequipped " << item.name << " (Attack recovered)";
            }
            else if (item.type == ItemType::Armor)
            {
                player->SetDefense(player->GetDefense() - item.value);
                SS << "[System] Unequipped " << item.name << " (Defense recovered)";
            }
            LogSystem::PrintStringsOnLog({ SS.str() });
            break;
        }
    }

    equippedSlots[slotIndex] = -1;
}

void Inventory::EquipItem(int index)
{
    int actualIndex = index - 1;

    if (actualIndex < 0 || actualIndex >= (int)ownedItems.size())
    {
        LogSystem::PrintStringsOnLog({ "[System] Invalid item index!" });
        return;
    }

    Item& selectedItem = ownedItems[actualIndex];
    Character* player = Character::GetInstance();
    stringstream SS;

    if (selectedItem.type != ItemType::Weapon && selectedItem.type != ItemType::Armor)
    {
        SS << "[System] " << selectedItem.name << " cannot be equipped.";
        LogSystem::PrintStringsOnLog({ SS.str() });
        return;
    }

    int slotIndex = (selectedItem.type == ItemType::Weapon) ? (int)EquipSlot::Weapon : (int)EquipSlot::Armor;

    UnequipSlot(slotIndex);

    selectedItem.equiped = true;

    if (selectedItem.type == ItemType::Weapon)
    {
        player->SetAttack(player->GetAttack() + selectedItem.value);
        SS.str("");
        SS << "[Effect] Attack boosted by " << selectedItem.value << "!";
    }
    else
    {
        player->SetDefense(player->GetDefense() + selectedItem.value);
        SS.str("");
        SS << "[Effect] Defense boosted by " << selectedItem.value << "!";
    }
    LogSystem::PrintStringsOnLog({ SS.str() });

    equippedSlots[slotIndex] = selectedItem.id;

    SS.str("");
    SS << "[System] Equipped " << selectedItem.name << " to " << (slotIndex == 0 ? "Weapon" : "Armor") << " slot.";
    LogSystem::PrintStringsOnLog({ SS.str() });
}

void Inventory::SetColor(int color) const
{
    // Get the standard output handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Set the text attribute
    SetConsoleTextAttribute(hConsole, color);
}

string Inventory::PrintByRarity(Item item) const
{
    stringstream SS;
    int color = 7; // Default: White

    // Selection logic based on Rarity Enum
    switch (item.rarity)
    {
    case Rarity::Common:// White
        SS << TextFormat::WHITE << item.name << TextFormat::DEFAULT;
        return SS.str();
    case Rarity::Rare:// Green
        SS << TextFormat::GREEN << item.name << TextFormat::DEFAULT;
        return SS.str();
    case Rarity::Legendary:// Yellow/Gold
        SS << TextFormat::YELLOW << item.name << TextFormat::DEFAULT;
        return SS.str();
    default:// Default
        SS << TextFormat::WHITE << item.name << TextFormat::DEFAULT;
        return SS.str();
    }

}

void Inventory::RemoveItem(int index)
{
    if (index >= 0 && index < (int)ownedItems.size())
    {
        ownedItems.erase(ownedItems.begin() + index);
    }
}

void Inventory::SetTempAtkBuff(int buff)
{
    tempAtkBuff += buff;
}
