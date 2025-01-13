#pragma once
#include "Monster.h"

class Orc : public Monster {
public:
    // ������
    Orc(int level);

    // ����ǰ ���̺� �ʱ�ȭ
    void InitializeLootTable() override;

    // ����ǰ ���
    std::unique_ptr<Item> DropItem() override;
};
