#include "RevivePotion.h"
#include "Character.h"
#include <iostream>

// ������
RevivePotion::RevivePotion(const std::string& name, int price, int amount)
    : Item(name, price, amount) {
}

// Use �Լ� ���� (ĳ���� ��Ȱ ȿ��)
void RevivePotion::Use(Character* character) {
    if (character->Health <= 0) {
        character->Health = character -> MaxHealth / 2;  // ��Ȱ �� �ִ� ü���� �������� ����
        std::cout << Name << "�� ����Ͽ� ĳ���Ͱ� ��Ȱ�߽��ϴ�!\n";
    }
    else {
        std::cout << "�̹� ����ִ� ĳ�����Դϴ�.\n";
    }
}

// ��� Ÿ�� ��ȯ
Equipment* RevivePotion::GetType() const {
    static Equipment temp("��Ȱ ����", 50, 0, Equipment::EquipmentType::Consumable);
    return &temp;  // ���÷� �Һ� ���������� ����
}
