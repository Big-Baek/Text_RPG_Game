#pragma once
#include "Item.h"

class RevivePotion : public Item {
public:
    // �⺻ ������
    RevivePotion() : Item() {}
    // �����ڿ��� Item ������ ȣ��
    RevivePotion(const std::string& name, int price, int amount);
    std::string GetName() const override;
    void Use(Character* character) override;
};
