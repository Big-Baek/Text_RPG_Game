#pragma once
#include "Item.h"
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <unordered_map>

class Shop;

class Character {
public:
    std::string Name;
    int Level;
    int Health;
    int MaxHealth;
    int Attack;
    int AttackBoostAmount = 0;  // �������� ������ ���ݷ� ����
    int Experience;
    int Gold;

    // ����Ʈ �����͸� ����� �κ��丮 (�����۰� ����)
    // Character Ŭ������ Inventory ���� �ѱ۷� ����
    // std::unordered_map<std::string, int> Inventory;
    std::unordered_map<std::string, std::unique_ptr<Item>> Inventory; // �����ͷ� ����

    Character(const std::string& name);
    void LevelUp();
    void GainExperience(int exp);
    void TakeDamage(int damage);
    void DisplayStatus() const;
    void VisitShop(Shop* shop);
    void ShowInventory() const;
    void AddItem(std::unique_ptr<Item> item) {
        const std::string& itemName = item->GetName();
        if (Inventory.find(itemName) == Inventory.end()) {
            Inventory[itemName] = std::move(item);  // �� ������ �߰�
        }
        else {
            // �̹� �����ϴ� �������� �ִٸ�, ������ ������Ŵ
            Inventory[itemName]->IncreaseAmount(item->GetAmount());
        }
    }
    void SellItemAtShop(Shop* shop);
    void AutoUseItems();  // ���� �� �ڵ� ��� ���

    void ResetAttackBoost();  // ���ݷ� �ʱ�ȭ �Լ� �߰�
};
