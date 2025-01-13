#include "AttackBoost.h"
#include "Character.h"
#include <iostream>

AttackBoost::AttackBoost()
    : Item("���ݷ� ����", 50) {  // �θ� Ŭ������ �ѱ� �̸� ����
}

std::string AttackBoost::GetName() const {
    return Name;  // �θ� Ŭ�������� �ʱ�ȭ�� Name�� ��ȯ
}

void AttackBoost::Use(Character* character) {
    character->Attack += 10;
    std::cout << character->Name << "�� ���ݷ� 10 ����!(�������� ���� �� �ʱ�ȭ)\n";
}
