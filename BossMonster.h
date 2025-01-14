// BossMonster.h
#pragma once
#include "Monster.h"
#include "Item.h"
#include <memory>
#include <vector>

class BossMonster : public Monster {
public:
    BossMonster(int level);

    // ����ǰ ���̺� �ʱ�ȭ
    void InitializeLootTable() override;

    // ����ǰ ���
    std::unique_ptr<Item> DropItem() override;
};
