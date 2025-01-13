// Item.h
#pragma once
#include <string>

class Item {
public:
    std::string Name;
    int Price;  // ���� �߰�

    Item(const std::string& name, int price) : Name(name), Price(price) {}

    virtual std::string GetName() const = 0;
    virtual void Use(class Character* character) = 0;

    virtual int GetPrice() const { return Price; }  // �⺻ ���� ��ȯ
    virtual ~Item() = default;
};
