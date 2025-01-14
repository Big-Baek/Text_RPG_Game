#pragma once
#include "Item.h"  // Item.h ����

class Equipment : public Item 
{

    public:
        enum class EquipmentType 
        {
            Weapon,
            Armor,
            Accessory,
            Consumable,
            Misc
        };
        // Type�� ���� Getter
        EquipmentType GetEquimentType() const { return Type; } // EquipmentType ��ȯ

        // Equipment Ŭ���� ���ο��� CompareEquipmentType �Լ� ����
        // static���� ���ǵ� �Լ��� �񱳸� �ܼ�ȭ�� �� �ֽ��ϴ�.
        static bool CompareEquipmentType(Equipment::EquipmentType lhs, Equipment::EquipmentType rhs) {
            return lhs == rhs;
        }



        Equipment(const std::string& name, int price, int bonusStat, EquipmentType type);

        // �޼��� �������̵�
        void Use(class Character* character) override;

        std::string GetName() const override;
        int GetBonusStat() const override;
        int GetPrice() const override;
        bool IsEquipable() const override;
    
        Equipment* GetType() const override;  // ��ȯ ������ Equipment*�� ����

    private:
        int BonusStat;
        EquipmentType Type;
};
