#include "Slime.h"
#include "Item.h"
#include <iostream>
#include <random>

// ������ ü�� ������ Ŭ���� ���� (SlimeJelly Ŭ����)
class SlimeJelly : public Item {
public:
    SlimeJelly() : Item("������ ü��", 10) {}

    std::string GetName() const override {
        return Name;
    }

    void Use(class Character* character) override {
        std::cout << "������ ü���� ���������, �ƹ� �ϵ� �Ͼ�� �ʾҽ��ϴ�.\n";
    }

    int GetPrice() const override { return 10; }  // ������ ü�� ����
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
    LootTable.emplace_back(std::make_unique<SlimeJelly>());
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
