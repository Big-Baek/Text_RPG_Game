#pragma once
#include "Monster.h"

class Goblin : public Monster {
public:
    Goblin(int level);

    // ����ǰ ���̺� �ʱ�ȭ
    void InitializeLootTable() override;

    // ����ǰ ���
    std::unique_ptr<Item> DropItem() override;
};
