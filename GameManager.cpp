#include "GameManager.h"
#include <iostream>
#include <cstdlib>  // rand() �Լ� ���
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "RevivePotion.h"
#include "Equipment.h"
#include <map>
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
            VisitShop(player, shop, this);  // gameManager �����ϰ� ���� ȣ��
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
// ���� ���� ����
std::unique_ptr<BossMonster> GameManager::GenerateBossMonster(int level)
{
    std::cout << "������ ���� �����ߴ�!\n";
    return std::make_unique<BossMonster>(level);  // BossMonster Ŭ������ ���
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
                // ���� ��� �� ���¸� ��� (EquippedArmor�� ���� �߰� ������ �̹� �ݿ���)
                int damageToPlayer = std::max(0, monster->Attack - player->Defense); // ���� ����
                std::cout << monster->Name << "�� ����! " << player->Name << "�� ü���� " << player->Health << "�� ����!\n";
                player->TakeDamage(damageToPlayer);
            }

            // ���� ���
            std::cout << player->Name << "�� ü��: " << player->Health << "\n";
            std::cout << monster->Name << "�� ü��: " << monster->Health << "\n";
        }

        // ���� ���
        if (monster->Health <= 0)
        {
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
        else
        {
            std::cout << player->Name << "��(��) ���������ϴ�. ���� ����.\n";
            exit(0);  // ���α׷� ����
        }
    }
    else
    {
        std::cout << "���Ͱ� �������� �ʽ��ϴ�!\n";
    }
    player->DisplayStatus();  // ���� �� ���� ǥ��
}

void GameManager::BossBattle(Character* player)
{
    // ���� ���� ���� ���� (���� ���ʹ� ������ �ɷ�ġ�� ���� �� ����)
    std::unique_ptr<Monster> boss = GenerateBossMonster(player->Level);

    // ���� ���� ���� ������ �ڵ� ���
    player->AutoUseItems();

    std::cout << boss->Name << "�� ��Ÿ����!\n";
    std::cout << "���� ����: " << boss->Level << "\n";
    std::cout << "���� ü��: " << boss->Health << "\n";
    std::cout << "���� ���ݷ�: " << boss->Attack << "\n";

    // ���� ���Ͱ� �����ϸ� ���� ����
    if (boss != nullptr)
    {
        std::cout << player->Name << "�� " << boss->Name << "�� ���� ������ ���۵˴ϴ�!\n";
        while (boss->Health > 0 && player->Health > 0)
        {
            // �÷��̾��� ����
            std::cout << player->Name << "�� ����! " << boss->Name << "�� ü���� " << boss->Health << "�� ����!\n";
            boss->TakeDamage(player->Attack);

            // ������ ����ִٸ� ������ ����
            if (boss->Health > 0)
            {
                // ���� ��� �� ���¸� ��� (EquippedArmor�� ���� �߰� ������ �̹� �ݿ���)
                int damageToPlayer = std::max(0, boss->Attack - player->Defense); // ���� ����
                std::cout << boss->Name << "�� ����! " << player->Name << "�� ü���� " << player->Health << "�� ����!\n";
                player->TakeDamage(damageToPlayer);
            }

            // ���� ���
            std::cout << player->Name << "�� ü��: " << player->Health << "\n";
            std::cout << boss->Name << "�� ü��: " << boss->Health << "\n";
        }

        // ���� ���
        if (boss->Health <= 0)
        {
            std::cout << boss->Name << "�� óġ�߽��ϴ�!\n";
            player->GainExperience(500);  // ���� óġ �� ���� ����ġ ȹ��

            // ����ǰ ���
            std::unique_ptr<Item> loot = boss->DropItem();
            if (loot != nullptr) {
                std::cout << "����ǰ���� " << loot->GetName() << "��(��) ȹ���߽��ϴ�!\n";
                player->AddItem(std::move(loot));  // �κ��丮�� ������ �߰�
            }
            else {
                std::cout << "����ǰ�� �����ϴ�.\n";
            }

            // ���� Ŭ���� �޽��� ���
            std::cout << player->Name << "��, ������ óġ�Ͽ� ������ Ŭ�����߽��ϴ�!\n";
            std::cout << "�����մϴ�! ������ Ŭ�����ϼ̽��ϴ�!\n";

            // ���� ���� ó��
            exit(0);  // ���α׷� ����
        }
        else
        {
            std::cout << player->Name << "��(��) ���������ϴ�. ���� ����.\n";
            exit(0);  // ���α׷� ����
        }
    }
    else {
        std::cout << "���� ���Ͱ� �������� �ʽ��ϴ�!\n";
    }

    player->DisplayStatus();  // ���� �� ���� ǥ��
}

void GameManager::VisitShop(Character* player, Shop* shop, GameManager* gameManager)
{
    while (true)
    {
        std::cout << "������ ���� ���� ȯ���մϴ�! ������ �Ͻðڽ��ϱ�?\n";
        std::cout << "1. ��� ������ ����\n";
        std::cout << "2. ��� ������ ����\n";
        std::cout << "3. ������ �Ǹ�\n";
        std::cout << "4. ������ ��� Ȯ��\n";
        std::cout << "5. ���� ���� (���ڸ� �Է����ּ���): ";

        int choice;
        std::cin >> choice;

        int index = 0;
        std::vector<std::string> itemNames;
        std::unordered_map<std::string, std::unique_ptr<Item>>::iterator itemToSell;  // ���⼭ �ʱ�ȭ���ָ� ��

        switch (choice)
        {
        case 1:  // ��� ������ ����
            std::cout << "\n��� ������ ����Դϴ�. ���� ���� ���(" << player->Gold << ")\n";
            std::cout << "1. ü�� ���� (20 ���)\n";
            std::cout << "2. ���ݷ� ���� (50 ���)\n";
            std::cout << "3. ��Ȱ ���� (100 ���)\n";
            std::cout << "4. �ڷΰ���\n";

            int buyChoice;
            std::cin >> buyChoice;

            switch (buyChoice)
            {
            case 1:  // ü�� ����
                if (player->Gold >= 20)
                {
                    auto it = player->Inventory.find("ü�� ����");
                    if (it != player->Inventory.end())
                    {
                        it->second->IncreaseAmount(1);
                    }
                    else
                    {
                        player->AddItem(std::make_unique<HealthPotion>("ü�� ����", 20, 1));
                    }
                    player->Gold -= 20;
                    std::cout << "ü�� ������ �����߽��ϴ�.\n";
                }
                else
                {
                    std::cout << "��尡 �����մϴ�.\n";
                }
                break;

            case 2:  // ���ݷ� ����
                if (player->Gold >= 50)
                {
                    auto it = player->Inventory.find("���ݷ� ����");
                    if (it != player->Inventory.end())
                    {
                        it->second->IncreaseAmount(1);
                    }
                    else
                    {
                        player->AddItem(std::make_unique<AttackBoost>("���ݷ� ����", 50, 1));
                    }
                    player->Gold -= 50;
                    std::cout << "���ݷ� ������ �����߽��ϴ�.\n";
                }
                else
                {
                    std::cout << "��尡 �����մϴ�.\n";
                }
                break;

            case 3:  // ��Ȱ ����
                if (player->Gold >= 100)
                {
                    auto it = player->Inventory.find("��Ȱ ����");
                    if (it != player->Inventory.end())
                    {
                        it->second->IncreaseAmount(1);
                    }
                    else
                    {
                        player->AddItem(std::make_unique<RevivePotion>("��Ȱ ����", 100, 1));
                    }
                    player->Gold -= 100;
                    std::cout << "��Ȱ ������ �����߽��ϴ�.\n";
                }
                else
                {
                    std::cout << "��尡 �����մϴ�.\n";
                }
                break;

            case 4:  // �ڷΰ���
                std::cout << "�������� ���ư��ϴ�.\n";
                break;
            }
            break;

        case 2:  // ��� ������ ����
            std::cout << "\n��� ������ ����Դϴ�. ���� ���� ���(" << player->Gold << ")\n";
            std::cout << "1. ��� (100 ���)\n";
            std::cout << "2. �������� (100 ���)\n";
            std::cout << "3. ������ (200 ���)\n";
            std::cout << "4. �������� (200 ���)\n";
            std::cout << "5. �ڷΰ���\n";

            std::cin >> buyChoice;

            switch (buyChoice)
            {
            case 1:  // ��� (����)
                gameManager->PurchaseEquipment(player, "���", 100, 3, Equipment::EquipmentType::Weapon);
                break;

            case 2:  // �������� (��)
                gameManager->PurchaseEquipment(player, "��������", 100, 5, Equipment::EquipmentType::Armor);
                break;

            case 3:  // ������ (����)
                gameManager->PurchaseEquipment(player, "������", 200, 5, Equipment::EquipmentType::Weapon);
                break;

            case 4:  // �������� (��)
                gameManager->PurchaseEquipment(player, "��������", 200, 7, Equipment::EquipmentType::Armor);
                break;

            case 5:  // �ڷΰ���
                std::cout << "�������� ���ư��ϴ�.\n";
                break;

            default:
                std::cout << "�߸��� �����Դϴ�. �ٽ� �õ��� �ּ���.\n";
                break;
            }
            break;

        case 3:  // ������ �Ǹ�
            std::cout << "�Ǹ��� �������� �����ϼ���.\n";
            std::cout << "���� ������ ������ ���:\n";
            index = 1;

            // ������ ��� ���
            for (const auto& item : player->Inventory) {
                std::cout << index++ << ". " << item.first << ": " << item.second->GetAmount() << " ��\n";
            }

            std::cout << "�Ǹ��� ������ ��ȣ�� �Է��ϼ���: ";
            int sellChoice;
            std::cin >> sellChoice;

            if (sellChoice < 1 || sellChoice >= index) {
                std::cout << "�߸��� ��ȣ�Դϴ�.\n";
                break;
            }

            // �Ǹ��� ������ ã��
            itemToSell = player->Inventory.begin();
            std::advance(itemToSell, sellChoice - 1);  // �Ǹ��� ���������� �̵�

            std::cout << itemToSell->first << "�� �Ǹ��߽��ϴ�.\n";
            player->Gold += itemToSell->second->GetPrice();  // �Ǹ� �ݾ׸�ŭ ��� �߰�
            player->Inventory.erase(itemToSell);  // ������ ����
            break;

        case 4:  // ������ ��� Ȯ��
            std::cout << "���� ������ ������ ���:\n";
            index = 1;
            for (const auto& item : player->Inventory) {
                std::cout << index++ << ". " << item.first << ": " << item.second->GetAmount() << " ��\n";
            }
            break;

        case 5:  // ���� ����
            std::cout << "������ �����մϴ�.\n";
            return;

        default:
            std::cout << "�߸��� �����Դϴ�. �ٽ� �õ��� �ּ���.\n";
            break;
        }
    }
}


void GameManager::PurchaseEquipment(Character* player, const std::string& itemName, int price, int bonusStat, Equipment::EquipmentType type)
{
    if (player->Gold >= price)
    {
        // ��� �̹� �κ��丮�� �ִ��� Ȯ��
        auto it = player->Inventory.find(itemName);
        if (it != player->Inventory.end()) // �̹� ������ �ִ� ���
        {
            it->second->IncreaseAmount(1);  // ���� ����
        }
        else // ���ο� ��� ����
        {
            // Equipment ��ü�� std::unique_ptr<Item>�� ��ȯ�Ͽ� ����
            std::unique_ptr<Item> item = std::move(std::make_unique<Equipment>(itemName, price, bonusStat, type));

            // AddItem���� std::move(item)�� ���� �������� �ѱ�ϴ�.
            player->AddItem(std::move(item));  // AddItem �Լ����� �������� ����
        }

        player->Gold -= price;  // ��� ����
        std::cout << itemName << "��(��) �����߽��ϴ�.\n";
    }
    else
    {
        std::cout << "��尡 �����մϴ�.\n";
    }
}




void GameManager::DisplayInventory(Character* player)
{
    std::cout << "�κ��丮:\n";
    for (const auto& item : player->Inventory)
    {
        std::cout << item.first << ": " << item.second->GetName() << " (" << item.second -> GetAmount() << " ��)\n";
    }
}
