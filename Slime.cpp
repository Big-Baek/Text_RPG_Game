#include "Slime.h"
#include "Item.h"
#include "Equipment.h"
#include <iostream>
#include <random>

// ������ ü�� ������ Ŭ���� ���� (SlimeJelly Ŭ����)
class SlimeFluid : public Item {
public:
    SlimeFluid() : Item("������ ü��", 15) {}

    std::string GetName() const override {
        return Name;
    }

    void Use(class Character* character) override {
        std::cout << "������ ü���� �Ⱦ� ��带 ������ϴ�.\n";
    }

    int GetPrice() const override {
        return 15;  // ������ ü�� ����
    }

    Equipment* GetType() const override {
        static Equipment temp("������ ü��", 15, 0, Equipment::EquipmentType::Misc);
        return &temp;
    }
};



Slime::Slime(int level)
    : Monster(level) {
    Name = "������";
    Health = 50 + (level * 10);
    Attack = 5 + (level * 2);
    Defense = 2 + (level * 2);
    InitializeLootTable();
}

void Slime::InitializeLootTable() {
    LootTable.emplace_back(std::make_unique<SlimeFluid>());
}

std::unique_ptr<Item> Slime::DropItem() {
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
