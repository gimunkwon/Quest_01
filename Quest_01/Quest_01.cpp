#include <iostream>
#include <vector>
#include <string>
#include "Character.h"

#define PotionHealingValue 20

using namespace std;


enum class E_PotionType : uint8_t
{
    HP_Potion,
    MP_Potion,
};

static int temp1{}, temp2{};
static int CurrentKeyNumber{1};

#pragma region Function
// string 문자열을 입력시 출력해주는 함수
void ShowStatText(string text1, string text2);
// 포션을 충전하는 함수
void setPotion(int count, int* p_HPPotion, int* p_MPPotion);
// 포션 갯수 게터 함수
int GetPotion(int* p_HPPotion, int* p_MPPotion);
// 포션을 사용하는 함수
void UsePotion(E_PotionType Potion_Type, int count, int* p_HPPotion,int* p_MPPotion, Character* Player);
// 능력치를 강화하는 함수
void GrowStat(E_Stat GrowType, int value, Character* Player);
// 레벨업 함수
void LevelUp(Character* Player);
#pragma endregion 

#pragma region MainFunction
int main()
{
#pragma region SettingStat
    vector<int> InjectionStat(4,0);
    
    // 스탯 주입 로직
    for (int i = 0; i < InjectionStat.size() / 2; i++)
    {
        while (temp1 <= 0 || temp2 <= 0)
        {
            if (i == 0)
            {
                ShowStatText("HP","MP");
                
            }
            else if (i == 1)
            {
                ShowStatText("공격력","방어력");
            }
            
            if (temp1 <= 0 || temp2 <= 0)
            {
                cout << "다시 입력하세요" << "\n";
            }
            else
            {
                if (i == 0)
                {
                    InjectionStat[0] = temp1;
                    InjectionStat[1] = temp2;
                    
                    temp1 = 0;
                    temp2 = 0;
                }
                else if (i == 1)
                {
                    InjectionStat[2] = temp1;
                    InjectionStat[3] = temp2;
                }
                break;
            }
        }
    }
    
    // 로그 출력
    for (int i = 0; i < InjectionStat.size(); ++i)
    {
        cout << InjectionStat[i] << "\n";
    }
#pragma endregion
    
    
    Character* Player = new Character(InjectionStat[0], InjectionStat[1], InjectionStat[2], InjectionStat[3]);
    
    int HPPotion{}, MPPotion{};
    
    // 포션 충전
    setPotion(5, &HPPotion, &MPPotion);
    
    // 확인용
    cout << HPPotion << MPPotion << "\n";
    
    while (CurrentKeyNumber != 0)
    {
        cout << "=================" << "\n";
        cout << "1. HP UP" << "\n";
        cout << "2. MP UP" << "\n";
        cout << "3. 공격력 Up" << "\n";
        cout << "4. 방어력 Up" << "\n";
        cout << "5. 현재 능력치" << "\n";
        cout << "6. Level Up" << "\n";
        cout << "0. 나가기" << "\n";
        cout << "번호를 입력 해주세요 : " << " ";
        
        cin >> CurrentKeyNumber;
        
        switch (CurrentKeyNumber)
        {
        case 0:
            cout << "프로그램을 종료합니다." << "\n";
            break;
        case 1:
            UsePotion(E_PotionType::HP_Potion, 1,&HPPotion,&MPPotion, Player);
            break;
        case 2:
            UsePotion(E_PotionType::MP_Potion, 1,&HPPotion,&MPPotion, Player);
            break;
        case 3:
            GrowStat(E_Stat::AttackPower,2,Player);
            break;
        case 4:
            GrowStat(E_Stat::ArmorPower,2,Player);
            break;
        case 5:
            cout << Player->GetAllStats() << "\n";
            cout << "남은 HP/MP 포션 수 :" << GetPotion(&HPPotion,nullptr) << "/" << GetPotion(nullptr,&MPPotion) << "\n";
            break;
        case 6:
            LevelUp(Player);
            setPotion(1, &HPPotion, &MPPotion);
            cout << "남은 HP/MP 포션 수 :" << GetPotion(&HPPotion,nullptr) << "/" << GetPotion(nullptr,&MPPotion) << "\n";
            break;
        }
    }
    
    
    
    
    delete Player;
}
#pragma endregion

void ShowStatText(const string text1, const string text2)
{
    cout << text1 << +"와(과)" << text2 << +"를(을)" << +"입력 해주세요 : " << " ";
    cin >> temp1 >> temp2;
}

void setPotion(int count, int* p_HPPotion, int* p_MPPotion)
{
    if (p_HPPotion)
    {
        *p_HPPotion += count;
    }
    if (p_MPPotion)
    {
        *p_MPPotion += count;
    }
}

int GetPotion(int* p_HPPotion, int* p_MPPotion)
{
    if (p_HPPotion)
    {
        return *p_HPPotion;
    }
    if (p_MPPotion)
    {
        return *p_MPPotion;
    }
}

void UsePotion(E_PotionType Potion_Type, int count, int* p_HPPotion,int* p_MPPotion, Character* Player)
{
    switch (Potion_Type)
    {
    case E_PotionType::HP_Potion :
        Player->SetStat(E_Stat::HP, PotionHealingValue);
        cout << "HP가" << PotionHealingValue << "증가되었습니다. 포션이" << count << "개 차감됩니다." << "\n";
        setPotion(-count, p_HPPotion,nullptr);
        cout << "현재 HP: " << Player->GetStat(E_Stat::HP) << "\n";
        cout << "남은 포션: " << GetPotion(p_HPPotion, nullptr) << "\n";
        break;
    case E_PotionType::MP_Potion :
        Player->SetStat(E_Stat::MP, PotionHealingValue);
        cout << "MP가" << PotionHealingValue << "증가되었습니다. 포션이" << count << "개 차감됩니다." << "\n";
        setPotion(-count, nullptr,p_MPPotion);
        cout << "현재 MP: " << Player->GetStat(E_Stat::MP) << "\n";
        cout << "남은 포션: " << GetPotion(nullptr, p_MPPotion) << "\n";
        break;
    }
}

void GrowStat(E_Stat GrowType, int value, Character* Player)
{
    switch (GrowType)
    {
    case E_Stat::AttackPower:
        cout << "공격력이" << value << "배로 증가되었습니다." << "\n";
        Player->SetStat(E_Stat::AttackPower, value);
        cout << "현재 공격력 :" << Player->GetStat(E_Stat::AttackPower) << "\n";
        break;
    case E_Stat::ArmorPower:
        cout << "방어력이" << value << "배로 증가되었습니다." << "\n";
        Player->SetStat(E_Stat::ArmorPower, value);
        cout << "현재 방어력 :" << Player->GetStat(E_Stat::ArmorPower) << "\n";
        break;
    }
}

void LevelUp(Character* Player)
{
    Player->SetStat(E_Stat::Level, 1);
    cout << "레벨업! HP/MP포션이 지급됩니다." << "\n";
}


