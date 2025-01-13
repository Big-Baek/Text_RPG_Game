#pragma once
#include "Character.h"
#include "Monster.h"
#include "BossMonster.h"
#include "Shop.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"
#include <memory>
#include <vector>
#include <random>

class GameManager {
public:
    // ���� ���� ���� (std::unique_ptr<Monster> ��ȯ)
    static std::unique_ptr<Monster> GenerateRandomMonster(int level);

    // ���� �帧 ���� �Լ�
    void StartGame(Character* player, Shop* shop);

    // ���� ���� ���� (std::unique_ptr<BossMonster> ��ȯ)
    static std::unique_ptr<BossMonster> GenerateBossMonster(int level);

    // ���� ó�� �Լ�
    static void Battle(Character* player);

    // ���� �湮 ó�� �Լ�
    static void VisitShop(Character* player, Shop* shop);

    // �κ��丮 Ȯ�� �Լ�
    static void DisplayInventory(Character* player);

    // ���� ���� ���� ó�� �Լ�
    void BossBattle(Character* player);
};
