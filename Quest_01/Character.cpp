#include "Character.h"

#include <iostream>
using namespace std;

int Character::GetStat(const E_Stat stat)
{
    switch (stat)
    {
    case E_Stat::HP :
        return m_HP;
    case E_Stat::MP :
        return m_MP;
    case E_Stat::AttackPower :
        return m_Attack_Power;
    case E_Stat::ArmorPower :
        return m_Armor_Power;
    case E_Stat::Level :
        return m_Level;
        break;
    }
}

string Character::GetAllStats()
{
    string Allstat = "HP: " + to_string(m_HP) + " " +  "MP: " + to_string(m_MP) + " "
    + "공격력 : " + to_string(m_Attack_Power) + " " + "방어력 : "+ to_string(m_Armor_Power) + " "+ "레벨 : " + to_string(m_Level);
    return Allstat;
}


void Character::SetStat(E_Stat stat, int value)
{
    switch (stat)
    {
    case E_Stat::HP :
        m_HP += value;
        break;
    case E_Stat::MP :
        m_MP += value;
        break;
    case E_Stat::AttackPower :
        m_Attack_Power *= value;
        break;
    case E_Stat::ArmorPower :
        m_Armor_Power *= value;
        break;
    case E_Stat::Level :
        m_Level += value;
        break;
    }
}
