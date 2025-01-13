#pragma once
#include "Item.h"

class AttackBoost : public Item {
public:
    // �⺻ ������
    AttackBoost() : Item() {}
    // �����ڿ��� Item ������ ȣ��
    AttackBoost(const std::string& name, int price, int amount);
    // �̸��� ���ݸ� ����, ������ �⺻�� 1�� ������
    std::string GetName() const override;
    void Use(Character* character) override;
};
