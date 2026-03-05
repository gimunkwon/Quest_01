#pragma once
#include <vector>
#include <string>

using namespace std;

enum class E_Stat
{
    HP,
    MP,
    AttackPower,
    ArmorPower,
    Level
};

class Character
{
public:
    int GetStat(E_Stat stat);
    string GetAllStats();
    void SetStat(E_Stat stat, int value);
    
    Character(int HP, int Mp, int Attack_Power, int Armor_Power) 
    : m_HP{HP},m_MP{Mp},m_Attack_Power{Attack_Power},m_Armor_Power{Armor_Power} {}
private:
    int m_HP{};
    int m_MP{};
    int m_Attack_Power{};
    int m_Armor_Power{};
    int m_Level{};
};
