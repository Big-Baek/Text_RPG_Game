#pragma once
#include "Item.h"

class RevivePotion : public Item {
public:
    RevivePotion();  // �⺻ ������ ����
    std::string GetName() const override;
    void Use(Character* character) override;
};
