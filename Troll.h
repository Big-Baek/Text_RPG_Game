#pragma once
#include "Monster.h"

class Troll : public Monster {
public:
    // ������
    Troll(int level);

    // ����ǰ ���̺� �ʱ�ȭ
    void InitializeLootTable() override;  // ���� �Լ� ������

    // ����ǰ ���
    std::unique_ptr<Item> DropItem() override;  // ���� �Լ� ������
};
