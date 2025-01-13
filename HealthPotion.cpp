#include "HealthPotion.h"
#include "Character.h"
#include <iostream>

HealthPotion::HealthPotion()
    : Item("ü�� ����", 20) {
}

std::string HealthPotion::GetName() const {
    return Name;  // ��ӹ��� Name ��� ������ ��ȯ
}

void HealthPotion::Use(Character* character) {
    character->Health += 50;
    if (character->Health > character->MaxHealth) {
        character->Health = character->MaxHealth;
    }
    std::cout << "ü�� ���� ����� ���� ü�� 50 ȸ��!\n";
}
