#pragma once
#include <string>


enum class ItemType 
{
    Weapon,
    Armor,
    Potion,
    Etc
};

enum class Rarity 
{ 
    Common,
    Rare,
    Legendary 
};

struct Item 
{
    int id;               // Unique identifier for the item
    std::string name;     // Display name of the item
    ItemType type;        // Category of the item
    Rarity rarity;
    int value;            // Numeric value (Damage, Defense, or Heal amount)
    int price;
    std::string desc;     // Flavor text or description
    int count; // If item exists, increase count instead of adding a new row.
    bool equiped;

    Item(int _id, std::string _name, ItemType _type, Rarity _rarity, int _value, int _price, std::string _desc, int _count, int _equiped)
        : id(_id), name(_name), type(_type), rarity(_rarity), value(_value), price(_price), desc(_desc), count(1), equiped(_equiped){
    }

    // Default constructor for empty item initialization
    Item() : id(0), name("None"), type(ItemType::Etc), rarity(Rarity::Common), value(0), price(0), desc(""), count(0) , equiped(false){}
};