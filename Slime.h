#pragma once
#include "Monster.h"

class Slime : public Monster {
public:
    // ������
    Slime(int level);

    // ����ǰ ���̺� �ʱ�ȭ
    void InitializeLootTable() override;

    // ����ǰ ���
    std::unique_ptr<Item> DropItem() override;
};
