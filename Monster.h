// Monster.h
#pragma once
#include "Item.h"
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <random>

class Monster {
public:
    std::string Name;
    int Health;
    int Attack;
    int Defense;
    int Level;
    std::vector<std::unique_ptr<Item>> LootTable; // ����ǰ ���̺�

    // �⺻ ������
    Monster() : Name("Unknown"), Health(100), Attack(10), Defense(5), Level(1) {}

    // ���� ��� ������
    Monster(int level) : Name("Unknown"), Health(100 + level * 10), Attack(10 + level * 2), Defense(5 + level), Level(level) {}

    // �̸�, ü��, ���ݷ�, ���� ��� ������
    Monster(const std::string& name, int health, int attack, int defense)
        : Name(name), Health(health), Attack(attack), Defense(defense), Level(1) {
    }

    // ���ظ� ������ ü�� ����
    void TakeDamage(int damage) {
        Health -= damage;
        std::cout << Name << "�� " << damage << "�� ���ظ� �Ծ����ϴ�!\n";
        if (Health < 0) {
            Health = 0;
        }
    }

    // ���Ͱ� �й��ߴ��� Ȯ��
    bool IsDefeated() const {
        return Health <= 0;
    }

    // �⺻ ������ ����
    virtual void InitializeLootTable() {
        // �⺻ ������ ����ִ� ����ǰ ���̺�
        LootTable.clear();
    }

    virtual std::unique_ptr<Item> DropItem() {
        if (LootTable.empty()) {
            std::cout << Name << "�� ����ǰ�� ������ ���� �ʽ��ϴ�.\n";
            return nullptr;
        }

        // �������� ����ǰ�� ����߸�
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, LootTable.size() - 1);

        int index = dist(gen);
        std::cout << Name << "�� " << LootTable[index]->GetName() << "�� ����߷Ƚ��ϴ�!\n";
        return std::move(LootTable[index]);
    }

    virtual ~Monster() = default;
};
