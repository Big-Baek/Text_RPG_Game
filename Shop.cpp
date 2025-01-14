#include "Shop.h"
#include "Character.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "RevivePotion.h"
#include "Equipment.h"
#include <iostream>
#include <memory>

Shop::Shop() 
{
    AvailableItems.emplace_back(std::make_unique<HealthPotion>("ü�� ����", 20, 1)); // 1 �߰�
    AvailableItems.emplace_back(std::make_unique<AttackBoost>("���ݷ� ����", 50, 1)); // 1 �߰�
    AvailableItems.emplace_back(std::make_unique<RevivePotion>("��Ȱ ����", 100, 1)); // 1 �߰�

    AvailableItems.emplace_back(std::make_unique<Equipment>("���", 100, 3, Equipment::EquipmentType::Weapon));
    AvailableItems.emplace_back(std::make_unique<Equipment>("��������", 100, 5, Equipment::EquipmentType::Armor));
    AvailableItems.emplace_back(std::make_unique<Equipment>("������", 200, 5, Equipment::EquipmentType::Weapon));
    AvailableItems.emplace_back(std::make_unique<Equipment>("��������", 200, 7, Equipment::EquipmentType::Armor));

    ItemDescriptions["ü�� ����"] = "ü���� ȸ���մϴ�.";
    ItemDescriptions["���ݷ� ����"] = "���ݷ��� �Ͻ������� ������ŵ�ϴ�.";
    ItemDescriptions["��Ȱ ����"] = "��� �� ���Ǿ� ü���� ȸ���մϴ�.";
    ItemDescriptions["���"] = "���ݷ��� 3 ������Ű�� ����.";
    ItemDescriptions["��������"] = "������ 5 ������Ű�� ��.";
    ItemDescriptions["������"] = "���ݷ��� 5 ������Ű�� ����.";
    ItemDescriptions["��������"] = "������ 7 ������Ű�� ��.";
}

void Shop::DisplayItems() const 
{
    std::cout << "���� �Ǹ� ������ ���:\n";
    for (size_t i = 0; i < AvailableItems.size(); ++i) 
    {
        std::cout << i + 1 << ". " << AvailableItems[i]->GetName() << " - "
            << AvailableItems[i]->GetPrice() << " ���\n";
    }
}

void Shop::BuyItem(int index, Character* player) {
    if (index < 0 || index >= AvailableItems.size()) {
        std::cout << "�߸��� �����Դϴ�.\n";
        return;
    }

    int price = AvailableItems[index]->GetPrice();
    if (player->Gold >= price) {
        player->Gold -= price;
        player->AddItem(std::move(AvailableItems[index]));
        AvailableItems.erase(AvailableItems.begin() + index);
        std::cout << "���� �Ϸ�!\n";
    }
    else {
        std::cout << "��尡 �����մϴ�.\n";
    }
}
// ������ �Ǹ�
void Shop::SellItem(const std::string& itemName, Character* player) 
{
    auto it = player->Inventory.find(itemName);
    if (it != player->Inventory.end() && it->second->GetAmount() > 0) {
        int sellPrice = it->second->GetPrice() / 2;
        player->Gold += sellPrice;
        it->second->DecreaseAmount(1);
        std::cout << itemName << "��(��) " << sellPrice << " ��忡 �Ǹ��߽��ϴ�.\n";
    }
    else {
        std::cout << "�� �������� ������ ���� �ʽ��ϴ�.\n";
    }
}
// ������ �� ����� �޼���(index ����)
void Shop::DisplayItemDetails(int index) const 
{
    if (index < 0 || index >= AvailableItems.size()) 
    {
        std::cout << "�߸��� ������ �����Դϴ�.\n";
        return;
    }

    const std::string& itemName = AvailableItems[index]->GetName();
    auto it = ItemDescriptions.find(itemName);
    if (it != ItemDescriptions.end()) 
    {
        std::cout << itemName << ": " << it->second << "\n";
    }
    else 
    {
        std::cout << itemName << ": ������ �����ϴ�.\n";
    }
}
