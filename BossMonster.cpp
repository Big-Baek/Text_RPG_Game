// BossMonster.cpp
#include "BossMonster.h"
#include "Item.h"
#include <iostream>
#include <random>

// ���� ������: ������ ��
class DemonLordSword : public Item {
public:
    DemonLordSword() : Item("������ ��", 100,1) {}

    std::string GetName() const override {
        return Name;
    }

    void Use(Character* character) override {
        std::cout << "������ ���� ���������, Ư���� ȿ���� �������ϴ�.\n";
    }
};

// BossMonster Ŭ���� ����
BossMonster::BossMonster(int level)
    : Monster(level) {
    Name = "����";
    Health = 500 + (level * 50);
    Attack = 50 + (level * 10);
    Defense = 40 + (level * 5);
    InitializeLootTable();
}

void BossMonster::InitializeLootTable() {
    LootTable.clear();  // ���� ����ǰ ���̺� �ʱ�ȭ
    LootTable.emplace_back(std::make_unique<DemonLordSword>());
}

std::unique_ptr<Item> BossMonster::DropItem() {
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
