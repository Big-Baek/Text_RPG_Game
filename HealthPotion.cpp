#include "HealthPotion.h"
#include "Character.h"
#include <iostream>

// ������
HealthPotion::HealthPotion(const std::string& name, int price, int amount)
    : Item(name, price, amount) {
}

// Use �Լ� ���� (ü�� ȸ�� ȿ��)
void HealthPotion::Use(Character* character) {
    character->Health += 50;  // ���÷� ü�� 50 ȸ��
    std::cout << Name << "�� ����Ͽ� ü���� 50��ŭ ȸ���Ǿ����ϴ�!\n";
}

// ��� Ÿ�� ��ȯ
Equipment* HealthPotion::GetType() const {
    static Equipment temp("ü�� ����", 50, 0, Equipment::EquipmentType::Consumable);
    return &temp;
}
