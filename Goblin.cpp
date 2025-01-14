#include "Goblin.h"
#include "Item.h"
#include "Equipment.h"
#include <iostream>
#include <random>

class GoblinSpear : public Item 
{
public:
    GoblinSpear() : Item("����� â", 20) {}

    std::string GetName() const override 
    {
        return Name;
    }

    void Use(class Character* character) override 
    {
        std::cout << "����� â�� �Ⱦ� ��带 ������ϴ�.\n";
    }

    int GetPrice() const override 
    {
        return 20;  // ����� â ����
    }

    Equipment* GetType() const override 
    {
        static Equipment temp("����� â", 20, 0, Equipment::EquipmentType::Misc);
        return &temp;
    }
};


Goblin::Goblin(int level)
    : Monster(level) {
    Name = "���";
    Health = 70 + (level * 12);
    Attack = 8 + (level * 3);
    Defense = 3 + (level * 2);
    InitializeLootTable();
}

void Goblin::InitializeLootTable() {
    LootTable.emplace_back(std::make_unique<GoblinSpear>());
}

std::unique_ptr<Item> Goblin::DropItem() {
    if (LootTable.empty()) {
        std::cout << Name << "�� ����ǰ�� ������ ���� �ʽ��ϴ�.\n";
        return nullptr;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, LootTable.size() - 1);

    int index = dist(gen);
    std::cout << Name << "�� " << LootTable[index]->GetName() << "�� ����Ʈ�Ƚ��ϴ�!\n";
    return std::move(LootTable[index]);
}
