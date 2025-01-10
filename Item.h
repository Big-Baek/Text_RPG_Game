#pragma once
#include <string>
#include <vector>

class Character;

class Item {
public:
    // ������ �̸� ����
    virtual std::string GetName() const = 0;
    // ������ ����� ���� �Լ�
    virtual void Use(Character* character) = 0;
    virtual ~Item() = default;
};