#include "GameManager.h"
#include <iostream>
#include <cstdlib>  // rand() �Լ� ���
std::unique_ptr<Monster> GameManager::GenerateRandomMonster(int level)
{
    int randomMonster = rand() % 4;  // 0���� 3���� ���� ���� ����

    std::unique_ptr<Monster> monster;

    switch (randomMonster) {
    case 0:
        std::cout << "�������� �����ƴ�!\n";
        monster = std::make_unique<Slime>(level);  // Slime Ŭ���� ���
        break;
    case 1:
        std::cout << "����� �����ƴ�!\n";
        monster = std::make_unique<Goblin>(level);  // Goblin Ŭ���� ���
        break;
    case 2:
        std::cout << "Ʈ���� �����ƴ�!\n";
        monster = std::make_unique<Troll>(level);  // Troll Ŭ���� ���
        break;
    case 3:
        std::cout << "��ũ�� �����ƴ�!\n";
        monster = std::make_unique<Orc>(level);  // Orc Ŭ���� ���
        break;
    default:
        std::cout << "�⺻ ���͸� �����ƴ�!\n";
        monster = std::make_unique<Monster>(level);  // �⺻ ����
        break;
    }

    return monster;  // ������ ���� ����
}





void GameManager::StartGame(Character* player, Shop* shop) 
{
    int choice;
    do {
        std::cout << "\n���� ����:\n";
        player->DisplayStatus();

        std::cout << "\n� Ȱ���� �Ͻðڽ��ϱ�?\n";
        std::cout << "1. ����\n2. ���� �湮\n3. �κ��丮 Ȯ��\n4. ���� ����\n";
        std::cout << "���ϴ� ������ �����ϼ���: ";
        std::cin >> choice;
        std::cin.ignore(); // ���� ����

        if (choice == 1) {
            

            // ���� 10 �̻��� �� ���� ���Ϳ� ����
            if (player->Level >= 10) {
                BossBattle(player);
                break;  // ���� ���� �� ���� ����
            }
            else {
                Battle(player);  // �Ϲ� ���Ϳ� ����
            }
        }
        else if (choice == 2) {
            VisitShop(player, shop);
        }
        else if (choice == 3) {
            DisplayInventory(player);
        }
        else if (choice == 4) {
            std::cout << "������ �����մϴ�.\n";
        }
        else {
            std::cout << "�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n";
        }
    } while (choice != 4);
}
void GameManager::Battle(Character* player)
{
    // ���� ���� ����
    std::unique_ptr<Monster> monster = GenerateRandomMonster(player->Level);

    // ���� ���� ���� ������ �ڵ� ���
    player->AutoUseItems();
    
    std::cout << "�߻� " << monster->Name << "�� ��Ÿ����!\n";
    std::cout << "���� �̸�: " << monster->Name << "\n";
    std::cout << "���� ����: " << monster->Level << "\n";
    std::cout << "���� ü��: " << monster->Health << "\n";
    std::cout << "���� ���ݷ�: " << monster->Attack << "\n";

    // ���Ͱ� �����ϸ� ���� ����
    if (monster != nullptr) {
        std::cout << player->Name << "�� " << monster->Name << "�� ������ ���۵˴ϴ�!\n";
        while (monster->Health > 0 && player->Health > 0) {
            std::cout << player->Name << "�� ����! " << monster->Name << "�� ü���� " << monster->Health << "�� ����!\n";
            monster->TakeDamage(player->Attack);

            if (monster->Health > 0) {
                std::cout << monster->Name << "�� ����! " << player->Name << "�� ü���� " << player->Health << "�� ����!\n";
                player->TakeDamage(monster->Attack);
            }

            // ���� ���
            std::cout << player->Name << "�� ü��: " << player->Health << "\n";
            std::cout << monster->Name << "�� ü��: " << monster->Health << "\n";
        }

        // ���� ���
        if (monster->Health <= 0) {
            std::cout << monster->Name << "�� óġ�߽��ϴ�!\n";
            player->GainExperience(100);  // ����ġ ȹ��
            // ����ǰ ���
            std::unique_ptr<Item> loot = monster->DropItem();
            if (loot != nullptr) {
                std::cout << "����ǰ���� " << loot->GetName() << "��(��) ȹ���߽��ϴ�!\n";
                player->AddItem(std::move(loot));  // �κ��丮�� ������ �߰�
            }
            else {
                std::cout << "����ǰ�� �����ϴ�.\n";
            }
        }
        else {
            std::cout << player->Name << "��(��) ���������ϴ�. ���� ����.\n";
            exit(0);  // ���α׷� ����
        }
    }
    else {
        std::cout << "���Ͱ� �������� �ʽ��ϴ�!\n";
    }
    player->DisplayStatus();  // ���� �� ���� ǥ��
}



// ���� ���� ����
std::unique_ptr<BossMonster> GameManager::GenerateBossMonster(int level) {
    std::cout << "������ �����ƴ�!\n";
    return std::make_unique<BossMonster>(level);  // BossMonster Ŭ������ ���
}

void GameManager::BossBattle(Character* player) {
    // ���� ������ ����
    auto boss = GenerateBossMonster(player->Level);  // ���� ���� ����
    std::cout << "���� ���� " << boss->Name << "�� ��Ÿ�����ϴ�!\n";

    // ���� ���� �� ���ݷ� ���� ������ ���
    player->AutoUseItems();

    while (boss->Health > 0 && player->Health > 0) {
        std::cout << "�÷��̾��� ����! " << boss->Name << "�� ü���� " << boss->Health << "�� ����!\n";
        boss->TakeDamage(player->Attack);

        // ������ ��� �ִٸ� ������ ����
        if (boss->Health > 0) {
            std::cout << boss->Name << "�� ����! " << player->Name << "�� ü���� " << player->Health << "�� ����!\n";
            player->TakeDamage(boss->Attack);
        }

        // �÷��̾�� ���� ���� ���
        std::cout << player->Name << "�� ���� ü��: " << player->Health << "\n";
        std::cout << boss->Name << "�� ���� ü��: " << boss->Health << "\n";
    }

    if (boss->Health <= 0) {
        std::cout << boss->Name << "�� óġ�߽��ϴ�! ���� Ŭ����!\n";
        player->GainExperience(500);  // ���� óġ �� ����ġ
    }
    else if (player->Health <= 0) {
        std::cout << player->Name << "��(��) ���������ϴ�. ���� ����.\n";
    }

    // ���� ���� �޽���
    std::cout << "������ �����մϴ�.\n";
}





void GameManager::VisitShop(Character* player, Shop* shop)
{
    while (true) {
        std::cout << "������ ���� ���� ȯ���մϴ�! ������ �Ͻðڽ��ϱ�?\n";
        std::cout << "1. ������ ����\n";
        std::cout << "2. ������ �Ǹ�\n";
        std::cout << "3. ������ ��� Ȯ��\n";
        std::cout << "4. ���� ����\n";

        int choice;
        std::cin >> choice;

        // ���⼭ ������ �ʱ�ȭ�ϵ��� ����
        int index;
        std::vector<std::string> itemNames;  // 'itemNames' ���� �ʱ�ȭ

        switch (choice) {
        case 1:  // ������ ����
            std::cout << "1. ü�� ���� (20 ���)\n";
            std::cout << "2. ���ݷ� ���� (50 ���)\n";
            std::cout << "3. ��Ȱ ���� (100 ���)\n";
            std::cout << "4. �ڷΰ���\n";
            int buyChoice;
            std::cin >> buyChoice;

            switch (buyChoice) {
            case 1:
                if (player->Gold >= 20)
                {
                    player->Inventory["ü�� ����"]++;
                    player->Gold -= 20;  // 20 ��� ����
                    std::cout << "ü�� ������ �����߽��ϴ�.\n";
                }
                else
                {
                    std::cout << "��尡 �����մϴ�.\n";
                }
                break;
            case 2:
                if (player->Gold >= 50)
                {
                    player->Inventory["���ݷ� ����"]++;
                    player->Gold -= 50;  // 50 ��� ����
                    std::cout << "���ݷ� ������ �����߽��ϴ�.\n";
                }
                else {
                    std::cout << "��尡 �����մϴ�.\n";
                }
                break;
            case 3:
                if (player->Gold >= 100)
                {
                    player->Inventory["��Ȱ ����"]++;  // ��Ȱ ���� �߰�
                    player->Gold -= 100;  // 100 ��� ����
                    std::cout << "��Ȱ ������ �����߽��ϴ�.\n";
                }
                else {
                    std::cout << "��尡 �����մϴ�.\n";
                }
                break;
            case 4:
                std::cout << "�������� ���ư��ϴ�.\n";
                break;
            default:
                std::cout << "�߸��� �����Դϴ�. �ٽ� �õ��� �ּ���.\n";
            }
            break;
        case 2:  // ������ �Ǹ�
            std::cout << "�Ǹ��� �������� �����ϼ���.\n";
            std::cout << "���� ������ ������ ���:\n";

            index = 1;  // 'index' �ʱ�ȭ

            // �÷��̾��� �κ��丮���� �Ǹ��� �������� ����
            for (const auto& item : player->Inventory) {
                if (item.second > 0) {  // �������� 1�� �̻� ���� ��쿡�� ǥ��
                    std::cout << index << ". " << item.first << ": " << item.second << "��\n";  // ������ ��� ���
                    itemNames.push_back(item.first);  // ������ �̸��� itemNames �迭�� �߰�
                    index++;  // �ε��� ����
                }
            }

            if (itemNames.empty()) {
                std::cout << "�Ǹ��� �������� �����ϴ�.\n";
                break;
            }

            std::cout << "0. �ڷΰ���\n";

            int sellChoice;
            std::cin >> sellChoice;

            if (sellChoice == 0) {
                std::cout << "�������� ���ư��ϴ�.\n";
                break;
            }

            // sellChoice�� ��ȿ�� �������� Ȯ��
            if (sellChoice < 0 || sellChoice > itemNames.size()) {
                std::cout << "�߸��� �����Դϴ�. �ٽ� �õ��� �ּ���.\n";
                break;
            }

            // ��ȿ�� sellChoice�� ���, ������ �Ǹ�
            if (sellChoice > 0 && sellChoice <= itemNames.size()) {
                std::string itemName = itemNames[sellChoice - 1];  // ���õ� ������ �̸�
                int itemCount = player->Inventory[itemName];

                if (itemCount > 0) {
                    shop->SellItem(itemName, player);  // ������ �Ǹ�
                }
                else {
                    std::cout << "�Ǹ��� " << itemName << "��(��) �����ϴ�.\n";
                }
            }
            break;

        case 3:  // ������ ��� Ȯ��
            std::cout << "���� ������ ������ ���:\n";
            for (const auto& item : player->Inventory) {
                std::cout << item.first << ": " << item.second << "��\n";
            }
            break;

        case 4:  // ���� ����
            std::cout << "������ �����մϴ�.\n";
            return;  // ���� ����

        default:
            std::cout << "�߸��� �����Դϴ�. �ٽ� �õ��� �ּ���.\n";
            break;
        }
    }
}



void GameManager::DisplayInventory(Character* player) 
{
    std::cout << "�κ��丮:\n";
    for (const auto& item : player->Inventory) {
        std::cout << item.first << ": " << item.second << " ��\n";
    }
}
