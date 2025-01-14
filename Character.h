#pragma once
#include "Equipment.h"
#include "Shop.h"
#include <unordered_map>  // unordered_map ��� �߰�
#include <string>

class Character {
public:
    std::string Name;
    int Level;
    int Health;
    int MaxHealth;
    int Attack;
    int AttackBoostAmount = 0;  // �������� ������ ���ݷ� ����
    int Experience;
    int Defense = 0; // ����(���θ� �ö�)
    int Gold;

    // ����Ʈ �����͸� ����ϴ� �κ��丮: �����۰� �ش� ������ ����
    std::unordered_map<std::string, std::unique_ptr<Item>> Inventory;

    Equipment* EquippedWeapon = nullptr;  // ������ ����
    Equipment* EquippedArmor = nullptr;   // ������ ��

    // ������
    Character(const std::string& name);

    // ������ �޼ҵ�
    void LevelUp();

    // ����ġ ȹ�� �޼ҵ�
    void GainExperience(int exp);

    // ������ �ޱ� �޼ҵ�
    void TakeDamage(int damage);

    // ĳ���� ���� ���
    void DisplayStatus() const;

    // ���� �湮 �޼ҵ�
    void VisitShop(Shop* shop);

    // �κ��丮 ǥ��
    void ShowInventory() const;

    // ������ �߰� �޼ҵ�
    void AddItem(std::unique_ptr<Item> item);

    // �������� ������ �Ǹ� �޼ҵ�
    void SellItemAtShop(Shop* shop);

    // ���� �� �ڵ� ������ ��� �޼ҵ�
    void AutoUseItems();

    // ���ݷ� �ʱ�ȭ �޼ҵ� (���� ���� ��)
    void ResetAttackBoost();

    // ��� ������ �ڵ� ���� �޼ҵ�
    void AutoEquipItems();

    // ���� ���� �޼ҵ�
    void EquipWeapon(Equipment* newWeapon);

    // �� ���� �޼ҵ�
    void EquipArmor(Equipment* newArmor);
   
    

};
