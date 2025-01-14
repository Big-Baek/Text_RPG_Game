#include "Orc.h"
#include "Item.h"
#include "Equipment.h"
#include <iostream>
#include <random>

class OrcAxe : public Item 
{
public:
    OrcAxe() : Item("��ũ�� ����", 25) {}

    std::string GetName() const override 
    {
        return Name;
    }

    void Use(class Character* character) override 
    {
        std::cout << "��ũ�� ������ �Ⱦ� ��带 ������ϴ�.\n";
    }

    int GetPrice() const override 
    {
        return 25;  // ��ũ�� ���� ����
    }

    Equipment* GetType() const override 
    {
        static Equipment temp("��ũ�� ����", 25, 0, Equipment::EquipmentType::Misc);
        return &temp;
    }
};

Orc::Orc(int level)
    : Monster(level) {
    Name = "��ũ";
    Health = 120 + (level * 18);
    Attack = 12 + (level * 5);
    Defense = 8 + (level * 4);
    InitializeLootTable();
}

void Orc::InitializeLootTable() {
    LootTable.emplace_back(std::make_unique<OrcAxe>());
}

std::unique_ptr<Item> Orc::DropItem() {
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
