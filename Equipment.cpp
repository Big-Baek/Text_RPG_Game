#include "item.h"
#include "Equipment.h"

Equipment::Equipment(const std::string& name, int price, int bonusStat, EquipmentType type)
    : Item(name, price), BonusStat(bonusStat), Type(type) {
}

void Equipment::Use(class Character* character) {
    // ���� ����
}

std::string Equipment::GetName() const {
    return Name;
}

int Equipment::GetBonusStat() const {
    return BonusStat;
}


int Equipment::GetPrice() const {
    return Price;
}

bool Equipment::IsEquipable() const {
    
    return true;  // ���÷� �׻� ���� �����ϵ��� ����
}

Equipment* Equipment::GetType() const {
    // EquipmentType�� Equipment*�� ��ȯ�Ͽ� ��ȯ�ϴ� ����
    return const_cast<Equipment*>(this);
}
