#pragma once
#include "Item.h"

class HealthPotion : public Item {
public:
    HealthPotion();  // �⺻ ������ ����
    std::string GetName() const override;
    void Use(Character* character) override;
};