#pragma once
#include "Item.h"

class RevivePotion : public Item {
public:
    // ������
    RevivePotion(const std::string& name, int price, int amount = 1);

    void Use(Character* character) override;  // Use �Լ� ����
    Equipment* GetType() const override;  // ��� Ÿ�� ��ȯ �Լ� ����
};
