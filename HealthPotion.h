#pragma once
#include "Item.h"

class HealthPotion : public Item {
public:
    // ������
    HealthPotion(const std::string& name, int price, int amount = 1);

    // Use �Լ� ���� (ü�� ȸ�� ȿ��)
    virtual void Use(Character* character) override;

    // ��� Ÿ�� ��ȯ (Equipment*�� ����)
    Equipment* GetType() const override;
};
