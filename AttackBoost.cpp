#include "AttackBoost.h"
#include "Character.h"
#include <iostream>


// Use �Լ� ���� (���ݷ� ���� ȿ��)
void AttackBoost::Use(Character* character) {
    character->Attack += GetBonusStat() + 10;  // BonusStat�� �⺻���� 0���� ����������, �ڽ� Ŭ�������� �������̵��� �� �ֽ��ϴ�.
    std::cout << Name << "�� ����Ͽ� ���ݷ��� " << GetBonusStat() << "��ŭ �����߽��ϴ�!\n";
}

// ��� Ÿ�� ��ȯ (Equipment*�� ��ȯ)
Equipment* AttackBoost::GetType() const {
    // Consumable Ÿ���� �ӽ� Equipment ��ü ��ȯ
    static Equipment temp("AttackBoost", 50, 1, Equipment::EquipmentType::Consumable);
    return &temp;
}
