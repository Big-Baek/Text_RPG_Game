#pragma once
#include "Item.h"
#include "Equipment.h"

class AttackBoost : public Item {
public:
    // ������
    AttackBoost(const std::string& name, int price, int amount = 1) {};

    // Use �Լ� ���� (���ݷ� ���� ȿ��)
    void Use(Character* character) override;

    // ��� Ÿ�� ��ȯ (Equipment*�� ����)
    Equipment* GetType() const override;
};
