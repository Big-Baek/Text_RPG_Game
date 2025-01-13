#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "RevivePotion.h"
#include <iostream>
#include <memory>

Shop::Shop() 
{
    AvailableItems.emplace_back(std::make_unique<HealthPotion>());
    AvailableItems.emplace_back(std::make_unique<AttackBoost>());
    AvailableItems.emplace_back(std::make_unique<RevivePotion>());

    // ������ ������ �ѱ۷� ó��
    ItemDescriptions["ü�� ����"] = "ü�� 50 ȸ��.";
    ItemDescriptions["���ݷ� ����"] = "���� �������� ���ݷ��� 10 ����.";
    ItemDescriptions["��Ȱ ����"] = "ĳ���͸� ��Ȱ��Ű�� ü���� ���� ä��ϴ�.";
}

// ������ ��� ǥ��
void Shop::DisplayItems() const 
{
    std::cout << "�Ǹ� ���� ������:\n";
    for (size_t i = 0; i < AvailableItems.size(); ++i) {
        std::cout << i + 1 << ". " << AvailableItems[i]->GetName() << " - "
            << (i == 0 ? 20 : 50) << " ���\n";
    }
}

// ������ ���� ����
void Shop::DisplayItemDetails(int index) const 
{
    if (index < 0 || index >= AvailableItems.size()) {
        std::cout << "�߸��� ������ �����Դϴ�.\n";
        return;
    }

    std::string itemName = AvailableItems[index]->GetName();
    std::cout << itemName << ": " << ItemDescriptions.at(itemName) << "\n";
}

// ������ ���� (����Ʈ ������ ����)
void Shop::BuyItem(int index, Character* player) 
{
    if (index < 0 || index >= AvailableItems.size()) {
        std::cout << "�߸��� ������ �����Դϴ�.\n";
        return;
    }

    int price = (index == 0 ? 20 : 50);
    if (player->Gold >= price) {
        player->Gold -= price;
        player->AddItem(std::move(AvailableItems[index]));
        AvailableItems.erase(AvailableItems.begin() + index);
        std::cout << "�� �������� �����߽��ϴ�!\n";
    }
    else {
        std::cout << "��尡 �����մϴ�.\n";
    }
}

void Shop::SellItem(const std::string& itemName, Character* player) 
{
    // 1. �κ��丮���� �������� ã���ϴ�.
    auto it = player->Inventory.find(itemName);
    if (it != player->Inventory.end() && it->second != 0) {
        // �������� �κ��丮�� ���� ��, �������� �ȱ�
        std::unique_ptr<Item>& item = it->second;  // �κ��丮���� ������ ��������

        // ������ ������ ��ü���� ������
        int sellPrice = item->GetPrice();  // GetPrice()�� �� ������ Ŭ�������� ���ǵǾ� �־�� ��

        // ��� ����
        player->Gold += sellPrice;
        player->Inventory.erase(it);  // �ش� �������� �κ��丮���� ����

        std::cout << itemName << "��(��) " << sellPrice << " ��忡 �Ǹ��߽��ϴ�. ���� ���� ��� :" <<player -> Gold <<"��� \n";
    }
    else {
        std::cout << "�� �������� ������ ���� �ʽ��ϴ�.\n";
    }
}




