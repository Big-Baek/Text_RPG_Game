#include "Troll.h"
#include "Item.h"
#include "Equipment.h"
#include <iostream>
#include <random>

class TrollClaw : public Item 
{
    public:
        TrollClaw() : Item("Ʈ���� ����", 30) {}

        std::string GetName() const override 
        {
            return Name;
        }

        void Use(class Character* character) override 
        {
            std::cout << "Ʈ���� ������ �Ⱦ� ��带 ������ϴ�.\n";
        }

        int GetPrice() const override 
        {
            return 30;  // Ʈ���� ���� ����
        }

        Equipment* GetType() const override 
        {
            static Equipment temp("Ʈ���� ����", 30, 0, Equipment::EquipmentType::Misc);
            return &temp;
        }
};

Troll::Troll(int level)
    : Monster(level) {
    Name = "Ʈ��";
    Health = 100 + (level * 15);
    Attack = 10 + (level * 4);
    Defense = 5 + (level * 3);
    InitializeLootTable();
}

void Troll::InitializeLootTable() {
    LootTable.emplace_back(std::make_unique<TrollClaw>());
}

std::unique_ptr<Item> Troll::DropItem() {
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
