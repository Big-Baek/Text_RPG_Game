#pragma once
#include "Item.h"

class HealthPotion : public Item {
public:
    // �⺻ ������
    HealthPotion() : Item() {}
    // �����ڿ��� Item ������ ȣ��
    HealthPotion(const std::string& name, int price, int amount);
    std::string GetName() const override;
    void Use(Character* character) override;
};