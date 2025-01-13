#include "Troll.h"
#include "Item.h"
#include <iostream>
#include <random>

// Ʈ���� ���� ������ Ŭ���� ���� (TrollClaw Ŭ����)
class TrollClaw : public Item {
public:
    TrollClaw() : Item("Ʈ���� ����", 20) {}

    std::string GetName() const override {
        return Name;
    }

    void Use(class Character* character) override {
        std::cout << "Ʈ���� ������ �Ⱦ� ��带 ������ϴ�.\n";
    }

    int GetPrice() const override { return 20; }  // Ʈ���� ���� ����
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
