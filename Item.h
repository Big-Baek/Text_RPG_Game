#pragma once
#include <string>

class Item {
public:
    std::string Name;
    int Price;  // ���� ���� ����
    int Amount;  // ������ ������ ����
    // �⺻ ������
    Item()
        : Name(""), Price(0), Amount(0) {
    }
    Item(const std::string& name, int price, int amount = 1)
        : Name(name), Price(price), Amount(amount) {
    }
    

    virtual std::string GetName() const { return Name; }
    virtual int GetPrice() const { return Price; }
    int GetAmount() const { return Amount; }

   
    // ���� ���� �Լ�
    void IncreaseAmount(int amount) {
        Amount += amount;  // ������ ����
    }
    // ���� ���� �Լ� �߰�
    void DecreaseAmount(int amount) {
        Amount -= amount;
        if (Amount < 0) {
            Amount = 0;  // ������ 0 ���Ϸ� �������� �ʰ� ó��
        }
    }
    virtual void Use(class Character* character) = 0;
    virtual ~Item() = default;
};
